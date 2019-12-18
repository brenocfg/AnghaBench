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
struct TYPE_2__ {int hw_buffer_size; int hw_queue_size; int /*<<< orphan*/  sw_buffer_size; } ;
struct rme32 {int /*<<< orphan*/  lock; scalar_t__ iobase; TYPE_1__ capture_pcm; scalar_t__ fullduplex_mode; } ;

/* Variables and functions */
 int RME32_BUFFER_SIZE ; 
 scalar_t__ RME32_IO_RESET_POS ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 struct rme32* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int snd_rme32_capture_prepare(struct snd_pcm_substream *substream)
{
	struct rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	if (rme32->fullduplex_mode) {
		memset(&rme32->capture_pcm, 0, sizeof(rme32->capture_pcm));
		rme32->capture_pcm.hw_buffer_size = RME32_BUFFER_SIZE;
		rme32->capture_pcm.hw_queue_size = RME32_BUFFER_SIZE / 2;
		rme32->capture_pcm.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	} else {
		writel(0, rme32->iobase + RME32_IO_RESET_POS);
	}
	spin_unlock_irq(&rme32->lock);
	return 0;
}