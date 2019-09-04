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
struct snd_rme9652 {scalar_t__ capture_pid; scalar_t__ playback_pid; int running; int control_register; scalar_t__ ss_channels; int /*<<< orphan*/  lock; int /*<<< orphan*/  channel_map; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int RME9652_DS ; 
 scalar_t__ RME9652_NCHANNELS ; 
 int /*<<< orphan*/  RME9652_control_register ; 
 int RME9652_freq ; 
 int /*<<< orphan*/  channel_map_9636_ds ; 
 int /*<<< orphan*/  channel_map_9636_ss ; 
 int /*<<< orphan*/  channel_map_9652_ds ; 
 int /*<<< orphan*/  channel_map_9652_ss ; 
 int rme9652_adat_sample_rate (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_start (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_stop (struct snd_rme9652*) ; 
 int /*<<< orphan*/  rme9652_write (struct snd_rme9652*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_rme9652_use_is_exclusive (struct snd_rme9652*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rme9652_set_rate(struct snd_rme9652 *rme9652, int rate)
{
	int restart;
	int reject_if_open = 0;
	int xrate;

	if (!snd_rme9652_use_is_exclusive (rme9652)) {
		return -EBUSY;
	}

	/* Changing from a "single speed" to a "double speed" rate is
	   not allowed if any substreams are open. This is because
	   such a change causes a shift in the location of 
	   the DMA buffers and a reduction in the number of available
	   buffers. 

	   Note that a similar but essentially insoluble problem
	   exists for externally-driven rate changes. All we can do
	   is to flag rate changes in the read/write routines.
	 */

	spin_lock_irq(&rme9652->lock);
	xrate = rme9652_adat_sample_rate(rme9652);

	switch (rate) {
	case 44100:
		if (xrate > 48000) {
			reject_if_open = 1;
		}
		rate = 0;
		break;
	case 48000:
		if (xrate > 48000) {
			reject_if_open = 1;
		}
		rate = RME9652_freq;
		break;
	case 88200:
		if (xrate < 48000) {
			reject_if_open = 1;
		}
		rate = RME9652_DS;
		break;
	case 96000:
		if (xrate < 48000) {
			reject_if_open = 1;
		}
		rate = RME9652_DS | RME9652_freq;
		break;
	default:
		spin_unlock_irq(&rme9652->lock);
		return -EINVAL;
	}

	if (reject_if_open && (rme9652->capture_pid >= 0 || rme9652->playback_pid >= 0)) {
		spin_unlock_irq(&rme9652->lock);
		return -EBUSY;
	}

	if ((restart = rme9652->running)) {
		rme9652_stop(rme9652);
	}
	rme9652->control_register &= ~(RME9652_freq | RME9652_DS);
	rme9652->control_register |= rate;
	rme9652_write(rme9652, RME9652_control_register, rme9652->control_register);

	if (restart) {
		rme9652_start(rme9652);
	}

	if (rate & RME9652_DS) {
		if (rme9652->ss_channels == RME9652_NCHANNELS) {
			rme9652->channel_map = channel_map_9652_ds;
		} else {
			rme9652->channel_map = channel_map_9636_ds;
		}
	} else {
		if (rme9652->ss_channels == RME9652_NCHANNELS) {
			rme9652->channel_map = channel_map_9652_ss;
		} else {
			rme9652->channel_map = channel_map_9636_ss;
		}
	}

	spin_unlock_irq(&rme9652->lock);
	return 0;
}