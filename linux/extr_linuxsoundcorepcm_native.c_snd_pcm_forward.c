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
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
typedef  scalar_t__ snd_pcm_sframes_t ;

/* Variables and functions */
 scalar_t__ do_pcm_hwsync (struct snd_pcm_substream*) ; 
 scalar_t__ forward_appl_ptr (struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_avail (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock_irq (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock_irq (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_sframes_t snd_pcm_forward(struct snd_pcm_substream *substream,
					 snd_pcm_uframes_t frames)
{
	snd_pcm_sframes_t ret;

	if (frames == 0)
		return 0;

	snd_pcm_stream_lock_irq(substream);
	ret = do_pcm_hwsync(substream);
	if (!ret)
		ret = forward_appl_ptr(substream, frames,
				       snd_pcm_avail(substream));
	snd_pcm_stream_unlock_irq(substream);
	return ret;
}