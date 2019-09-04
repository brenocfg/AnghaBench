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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sw_buffer_size; int /*<<< orphan*/  hw_buffer_size; } ;
struct rme32 {int wcreg; int /*<<< orphan*/  lock; scalar_t__ iobase; TYPE_1__ playback_pcm; scalar_t__ fullduplex_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  RME32_BUFFER_SIZE ; 
 scalar_t__ RME32_IO_CONTROL_REGISTER ; 
 scalar_t__ RME32_IO_RESET_POS ; 
 int RME32_WCR_MUTE ; 
 int RME32_WCR_SEL ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int snd_rme32_playback_prepare(struct snd_pcm_substream *substream)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	if (rme32->fullduplex_mode) {
		memset(&rme32->playback_pcm, 0, sizeof(rme32->playback_pcm));
		rme32->playback_pcm.hw_buffer_size = RME32_BUFFER_SIZE;
		rme32->playback_pcm.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	} else {
		writel(0, rme32->iobase + RME32_IO_RESET_POS);
	}
	if (rme32->wcreg & RME32_WCR_SEL)
		rme32->wcreg &= ~RME32_WCR_MUTE;
	writel(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme32->lock);
	return 0;
}