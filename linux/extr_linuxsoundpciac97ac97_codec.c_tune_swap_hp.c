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
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/ * ctl_find (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_rename_vol_ctl (struct snd_ac97*,char*,char*) ; 

__attribute__((used)) static int tune_swap_hp(struct snd_ac97 *ac97)
{
	if (ctl_find(ac97, "Headphone Playback Switch", NULL) == NULL)
		return -ENOENT;
	snd_ac97_rename_vol_ctl(ac97, "Master Playback", "Line-Out Playback");
	snd_ac97_rename_vol_ctl(ac97, "Headphone Playback", "Master Playback");
	return 0;
}