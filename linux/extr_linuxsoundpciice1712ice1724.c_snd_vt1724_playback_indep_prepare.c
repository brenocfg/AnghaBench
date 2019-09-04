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
struct snd_pcm_substream {int number; } ;
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BURST ; 
 int /*<<< orphan*/  ICEMT1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int snd_vt1724_pcm_prepare (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_vt1724_playback_indep_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	unsigned char val;

	spin_lock_irq(&ice->reg_lock);
	val = 3 - substream->number;
	if (inb(ICEMT1724(ice, BURST)) < val)
		outb(val, ICEMT1724(ice, BURST));
	spin_unlock_irq(&ice->reg_lock);
	return snd_vt1724_pcm_prepare(substream);
}