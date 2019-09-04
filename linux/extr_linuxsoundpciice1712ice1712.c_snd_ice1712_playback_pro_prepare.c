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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_ice1712 {int playback_pro_size; int /*<<< orphan*/  reg_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAYBACK_ADDR ; 
 int /*<<< orphan*/  PLAYBACK_COUNT ; 
 int /*<<< orphan*/  PLAYBACK_SIZE ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_buffer_bytes (struct snd_pcm_substream*) ; 
 int snd_pcm_lib_period_bytes (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_playback_pro_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_pro_size = snd_pcm_lib_buffer_bytes(substream);
	spin_lock_irq(&ice->reg_lock);
	outl(substream->runtime->dma_addr, ICEMT(ice, PLAYBACK_ADDR));
	outw((ice->playback_pro_size >> 2) - 1, ICEMT(ice, PLAYBACK_SIZE));
	outw((snd_pcm_lib_period_bytes(substream) >> 2) - 1, ICEMT(ice, PLAYBACK_COUNT));
	spin_unlock_irq(&ice->reg_lock);

	return 0;
}