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
struct snd_ice1712 {scalar_t__ ac97; } ;

/* Variables and functions */
 int snd_ac97_read (scalar_t__,int) ; 
 int /*<<< orphan*/  snd_ac97_write_cache (scalar_t__,int,int) ; 

__attribute__((used)) static int snd_vt1724_amp_add_controls(struct snd_ice1712 *ice)
{
	if (ice->ac97)
		/* we use pins 39 and 41 of the VT1616 for left and right
		read outputs */
		snd_ac97_write_cache(ice->ac97, 0x5a,
			snd_ac97_read(ice->ac97, 0x5a) & ~0x8000);
	return 0;
}