#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bdi_writeback {int /*<<< orphan*/  dirty_ratelimit; int /*<<< orphan*/  avg_write_bandwidth; } ;

/* Variables and functions */
 int DIRTY_POLL_THRESH ; 
 int HZ ; 
 long ilog2 (int /*<<< orphan*/ ) ; 
 long max (int,int) ; 
 long min (long,int) ; 
 unsigned long roundup_pow_of_two (int) ; 

__attribute__((used)) static long wb_min_pause(struct bdi_writeback *wb,
			 long max_pause,
			 unsigned long task_ratelimit,
			 unsigned long dirty_ratelimit,
			 int *nr_dirtied_pause)
{
	long hi = ilog2(wb->avg_write_bandwidth);
	long lo = ilog2(wb->dirty_ratelimit);
	long t;		/* target pause */
	long pause;	/* estimated next pause */
	int pages;	/* target nr_dirtied_pause */

	/* target for 10ms pause on 1-dd case */
	t = max(1, HZ / 100);

	/*
	 * Scale up pause time for concurrent dirtiers in order to reduce CPU
	 * overheads.
	 *
	 * (N * 10ms) on 2^N concurrent tasks.
	 */
	if (hi > lo)
		t += (hi - lo) * (10 * HZ) / 1024;

	/*
	 * This is a bit convoluted. We try to base the next nr_dirtied_pause
	 * on the much more stable dirty_ratelimit. However the next pause time
	 * will be computed based on task_ratelimit and the two rate limits may
	 * depart considerably at some time. Especially if task_ratelimit goes
	 * below dirty_ratelimit/2 and the target pause is max_pause, the next
	 * pause time will be max_pause*2 _trimmed down_ to max_pause.  As a
	 * result task_ratelimit won't be executed faithfully, which could
	 * eventually bring down dirty_ratelimit.
	 *
	 * We apply two rules to fix it up:
	 * 1) try to estimate the next pause time and if necessary, use a lower
	 *    nr_dirtied_pause so as not to exceed max_pause. When this happens,
	 *    nr_dirtied_pause will be "dancing" with task_ratelimit.
	 * 2) limit the target pause time to max_pause/2, so that the normal
	 *    small fluctuations of task_ratelimit won't trigger rule (1) and
	 *    nr_dirtied_pause will remain as stable as dirty_ratelimit.
	 */
	t = min(t, 1 + max_pause / 2);
	pages = dirty_ratelimit * t / roundup_pow_of_two(HZ);

	/*
	 * Tiny nr_dirtied_pause is found to hurt I/O performance in the test
	 * case fio-mmap-randwrite-64k, which does 16*{sync read, async write}.
	 * When the 16 consecutive reads are often interrupted by some dirty
	 * throttling pause during the async writes, cfq will go into idles
	 * (deadline is fine). So push nr_dirtied_pause as high as possible
	 * until reaches DIRTY_POLL_THRESH=32 pages.
	 */
	if (pages < DIRTY_POLL_THRESH) {
		t = max_pause;
		pages = dirty_ratelimit * t / roundup_pow_of_two(HZ);
		if (pages > DIRTY_POLL_THRESH) {
			pages = DIRTY_POLL_THRESH;
			t = HZ * DIRTY_POLL_THRESH / dirty_ratelimit;
		}
	}

	pause = HZ * pages / (task_ratelimit + 1);
	if (pause > max_pause) {
		t = max_pause;
		pages = task_ratelimit * t / roundup_pow_of_two(HZ);
	}

	*nr_dirtied_pause = pages;
	/*
	 * The minimal pause time will normally be half the target pause time.
	 */
	return pages >= DIRTY_POLL_THRESH ? 1 + t / 2 : t;
}