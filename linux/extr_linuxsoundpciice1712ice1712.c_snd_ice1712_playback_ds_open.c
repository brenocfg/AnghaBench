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
typedef  int u32 ;
struct snd_pcm_substream {size_t number; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; struct snd_pcm_substream** playback_con_substream_ds; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEDS (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTMASK ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_playback_ds ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ice1712_playback_ds_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	u32 tmp;

	ice->playback_con_substream_ds[substream->number] = substream;
	runtime->hw = snd_ice1712_playback_ds;
	spin_lock_irq(&ice->reg_lock);
	tmp = inw(ICEDS(ice, INTMASK)) & ~(1 << (substream->number * 2));
	outw(tmp, ICEDS(ice, INTMASK));
	spin_unlock_irq(&ice->reg_lock);
	return 0;
}