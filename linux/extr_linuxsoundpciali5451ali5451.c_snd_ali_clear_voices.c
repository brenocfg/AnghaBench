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
struct snd_ali {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_ali_disable_voice_irq (struct snd_ali*,unsigned int) ; 
 int /*<<< orphan*/  snd_ali_stop_voice (struct snd_ali*,unsigned int) ; 

__attribute__((used)) static void snd_ali_clear_voices(struct snd_ali *codec,
				 unsigned int v_min,
				 unsigned int v_max)
{
	unsigned int i;

	for (i = v_min; i <= v_max; i++) {
		snd_ali_stop_voice(codec, i);
		snd_ali_disable_voice_irq(codec, i);
	}
}