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
struct snd_pcm_substream {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_sframes_t ;

/* Variables and functions */
 int do_pcm_hwsync (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_calc_delay (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_pcm_delay(struct snd_pcm_substream *substream,
			 snd_pcm_sframes_t *delay)
{
	int err;
	snd_pcm_sframes_t n = 0;

	snd_pcm_stream_lock_irq(substream);
	err = do_pcm_hwsync(substream);
	if (!err)
		n = snd_pcm_calc_delay(substream);
	snd_pcm_stream_unlock_irq(substream);
	if (!err)
		*delay = n;
	return err;
}