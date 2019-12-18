#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int32 ;
typedef  int /*<<< orphan*/  WritebackContext ;
struct TYPE_2__ {scalar_t__ m_buf_alloc; int m_buf_written_clean; int /*<<< orphan*/  m_maxwritten_clean; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int BUF_REUSABLE ; 
 int BUF_WRITTEN ; 
 float BgWriterDelay ; 
 TYPE_1__ BgWriterStats ; 
 int /*<<< orphan*/  CurrentResourceOwner ; 
 int /*<<< orphan*/  DEBUG1 ; 
 int /*<<< orphan*/  DEBUG2 ; 
 long NBuffers ; 
 int /*<<< orphan*/  ResourceOwnerEnlargeBuffers (int /*<<< orphan*/ ) ; 
 int StrategySyncStart (scalar_t__*,scalar_t__*) ; 
 int SyncOneBuffer (int,int,int /*<<< orphan*/ *) ; 
 int bgwriter_lru_maxpages ; 
 float bgwriter_lru_multiplier ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,long,...) ; 

bool
BgBufferSync(WritebackContext *wb_context)
{
	/* info obtained from freelist.c */
	int			strategy_buf_id;
	uint32		strategy_passes;
	uint32		recent_alloc;

	/*
	 * Information saved between calls so we can determine the strategy
	 * point's advance rate and avoid scanning already-cleaned buffers.
	 */
	static bool saved_info_valid = false;
	static int	prev_strategy_buf_id;
	static uint32 prev_strategy_passes;
	static int	next_to_clean;
	static uint32 next_passes;

	/* Moving averages of allocation rate and clean-buffer density */
	static float smoothed_alloc = 0;
	static float smoothed_density = 10.0;

	/* Potentially these could be tunables, but for now, not */
	float		smoothing_samples = 16;
	float		scan_whole_pool_milliseconds = 120000.0;

	/* Used to compute how far we scan ahead */
	long		strategy_delta;
	int			bufs_to_lap;
	int			bufs_ahead;
	float		scans_per_alloc;
	int			reusable_buffers_est;
	int			upcoming_alloc_est;
	int			min_scan_buffers;

	/* Variables for the scanning loop proper */
	int			num_to_scan;
	int			num_written;
	int			reusable_buffers;

	/* Variables for final smoothed_density update */
	long		new_strategy_delta;
	uint32		new_recent_alloc;

	/*
	 * Find out where the freelist clock sweep currently is, and how many
	 * buffer allocations have happened since our last call.
	 */
	strategy_buf_id = StrategySyncStart(&strategy_passes, &recent_alloc);

	/* Report buffer alloc counts to pgstat */
	BgWriterStats.m_buf_alloc += recent_alloc;

	/*
	 * If we're not running the LRU scan, just stop after doing the stats
	 * stuff.  We mark the saved state invalid so that we can recover sanely
	 * if LRU scan is turned back on later.
	 */
	if (bgwriter_lru_maxpages <= 0)
	{
		saved_info_valid = false;
		return true;
	}

	/*
	 * Compute strategy_delta = how many buffers have been scanned by the
	 * clock sweep since last time.  If first time through, assume none. Then
	 * see if we are still ahead of the clock sweep, and if so, how many
	 * buffers we could scan before we'd catch up with it and "lap" it. Note:
	 * weird-looking coding of xxx_passes comparisons are to avoid bogus
	 * behavior when the passes counts wrap around.
	 */
	if (saved_info_valid)
	{
		int32		passes_delta = strategy_passes - prev_strategy_passes;

		strategy_delta = strategy_buf_id - prev_strategy_buf_id;
		strategy_delta += (long) passes_delta * NBuffers;

		Assert(strategy_delta >= 0);

		if ((int32) (next_passes - strategy_passes) > 0)
		{
			/* we're one pass ahead of the strategy point */
			bufs_to_lap = strategy_buf_id - next_to_clean;
#ifdef BGW_DEBUG
			elog(DEBUG2, "bgwriter ahead: bgw %u-%u strategy %u-%u delta=%ld lap=%d",
				 next_passes, next_to_clean,
				 strategy_passes, strategy_buf_id,
				 strategy_delta, bufs_to_lap);
#endif
		}
		else if (next_passes == strategy_passes &&
				 next_to_clean >= strategy_buf_id)
		{
			/* on same pass, but ahead or at least not behind */
			bufs_to_lap = NBuffers - (next_to_clean - strategy_buf_id);
#ifdef BGW_DEBUG
			elog(DEBUG2, "bgwriter ahead: bgw %u-%u strategy %u-%u delta=%ld lap=%d",
				 next_passes, next_to_clean,
				 strategy_passes, strategy_buf_id,
				 strategy_delta, bufs_to_lap);
#endif
		}
		else
		{
			/*
			 * We're behind, so skip forward to the strategy point and start
			 * cleaning from there.
			 */
#ifdef BGW_DEBUG
			elog(DEBUG2, "bgwriter behind: bgw %u-%u strategy %u-%u delta=%ld",
				 next_passes, next_to_clean,
				 strategy_passes, strategy_buf_id,
				 strategy_delta);
#endif
			next_to_clean = strategy_buf_id;
			next_passes = strategy_passes;
			bufs_to_lap = NBuffers;
		}
	}
	else
	{
		/*
		 * Initializing at startup or after LRU scanning had been off. Always
		 * start at the strategy point.
		 */
#ifdef BGW_DEBUG
		elog(DEBUG2, "bgwriter initializing: strategy %u-%u",
			 strategy_passes, strategy_buf_id);
#endif
		strategy_delta = 0;
		next_to_clean = strategy_buf_id;
		next_passes = strategy_passes;
		bufs_to_lap = NBuffers;
	}

	/* Update saved info for next time */
	prev_strategy_buf_id = strategy_buf_id;
	prev_strategy_passes = strategy_passes;
	saved_info_valid = true;

	/*
	 * Compute how many buffers had to be scanned for each new allocation, ie,
	 * 1/density of reusable buffers, and track a moving average of that.
	 *
	 * If the strategy point didn't move, we don't update the density estimate
	 */
	if (strategy_delta > 0 && recent_alloc > 0)
	{
		scans_per_alloc = (float) strategy_delta / (float) recent_alloc;
		smoothed_density += (scans_per_alloc - smoothed_density) /
			smoothing_samples;
	}

	/*
	 * Estimate how many reusable buffers there are between the current
	 * strategy point and where we've scanned ahead to, based on the smoothed
	 * density estimate.
	 */
	bufs_ahead = NBuffers - bufs_to_lap;
	reusable_buffers_est = (float) bufs_ahead / smoothed_density;

	/*
	 * Track a moving average of recent buffer allocations.  Here, rather than
	 * a true average we want a fast-attack, slow-decline behavior: we
	 * immediately follow any increase.
	 */
	if (smoothed_alloc <= (float) recent_alloc)
		smoothed_alloc = recent_alloc;
	else
		smoothed_alloc += ((float) recent_alloc - smoothed_alloc) /
			smoothing_samples;

	/* Scale the estimate by a GUC to allow more aggressive tuning. */
	upcoming_alloc_est = (int) (smoothed_alloc * bgwriter_lru_multiplier);

	/*
	 * If recent_alloc remains at zero for many cycles, smoothed_alloc will
	 * eventually underflow to zero, and the underflows produce annoying
	 * kernel warnings on some platforms.  Once upcoming_alloc_est has gone to
	 * zero, there's no point in tracking smaller and smaller values of
	 * smoothed_alloc, so just reset it to exactly zero to avoid this
	 * syndrome.  It will pop back up as soon as recent_alloc increases.
	 */
	if (upcoming_alloc_est == 0)
		smoothed_alloc = 0;

	/*
	 * Even in cases where there's been little or no buffer allocation
	 * activity, we want to make a small amount of progress through the buffer
	 * cache so that as many reusable buffers as possible are clean after an
	 * idle period.
	 *
	 * (scan_whole_pool_milliseconds / BgWriterDelay) computes how many times
	 * the BGW will be called during the scan_whole_pool time; slice the
	 * buffer pool into that many sections.
	 */
	min_scan_buffers = (int) (NBuffers / (scan_whole_pool_milliseconds / BgWriterDelay));

	if (upcoming_alloc_est < (min_scan_buffers + reusable_buffers_est))
	{
#ifdef BGW_DEBUG
		elog(DEBUG2, "bgwriter: alloc_est=%d too small, using min=%d + reusable_est=%d",
			 upcoming_alloc_est, min_scan_buffers, reusable_buffers_est);
#endif
		upcoming_alloc_est = min_scan_buffers + reusable_buffers_est;
	}

	/*
	 * Now write out dirty reusable buffers, working forward from the
	 * next_to_clean point, until we have lapped the strategy scan, or cleaned
	 * enough buffers to match our estimate of the next cycle's allocation
	 * requirements, or hit the bgwriter_lru_maxpages limit.
	 */

	/* Make sure we can handle the pin inside SyncOneBuffer */
	ResourceOwnerEnlargeBuffers(CurrentResourceOwner);

	num_to_scan = bufs_to_lap;
	num_written = 0;
	reusable_buffers = reusable_buffers_est;

	/* Execute the LRU scan */
	while (num_to_scan > 0 && reusable_buffers < upcoming_alloc_est)
	{
		int			sync_state = SyncOneBuffer(next_to_clean, true,
											   wb_context);

		if (++next_to_clean >= NBuffers)
		{
			next_to_clean = 0;
			next_passes++;
		}
		num_to_scan--;

		if (sync_state & BUF_WRITTEN)
		{
			reusable_buffers++;
			if (++num_written >= bgwriter_lru_maxpages)
			{
				BgWriterStats.m_maxwritten_clean++;
				break;
			}
		}
		else if (sync_state & BUF_REUSABLE)
			reusable_buffers++;
	}

	BgWriterStats.m_buf_written_clean += num_written;

#ifdef BGW_DEBUG
	elog(DEBUG1, "bgwriter: recent_alloc=%u smoothed=%.2f delta=%ld ahead=%d density=%.2f reusable_est=%d upcoming_est=%d scanned=%d wrote=%d reusable=%d",
		 recent_alloc, smoothed_alloc, strategy_delta, bufs_ahead,
		 smoothed_density, reusable_buffers_est, upcoming_alloc_est,
		 bufs_to_lap - num_to_scan,
		 num_written,
		 reusable_buffers - reusable_buffers_est);
#endif

	/*
	 * Consider the above scan as being like a new allocation scan.
	 * Characterize its density and update the smoothed one based on it. This
	 * effectively halves the moving average period in cases where both the
	 * strategy and the background writer are doing some useful scanning,
	 * which is helpful because a long memory isn't as desirable on the
	 * density estimates.
	 */
	new_strategy_delta = bufs_to_lap - num_to_scan;
	new_recent_alloc = reusable_buffers - reusable_buffers_est;
	if (new_strategy_delta > 0 && new_recent_alloc > 0)
	{
		scans_per_alloc = (float) new_strategy_delta / (float) new_recent_alloc;
		smoothed_density += (scans_per_alloc - smoothed_density) /
			smoothing_samples;

#ifdef BGW_DEBUG
		elog(DEBUG2, "bgwriter: cleaner density alloc=%u scan=%ld density=%.2f new smoothed=%.2f",
			 new_recent_alloc, new_strategy_delta,
			 scans_per_alloc, smoothed_density);
#endif
	}

	/* Return true if OK to hibernate */
	return (bufs_to_lap == 0 && recent_alloc == 0);
}