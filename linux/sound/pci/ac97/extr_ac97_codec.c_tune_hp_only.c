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
struct snd_kcontrol {void* put; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 void* bind_hp_volsw_put ; 
 struct snd_kcontrol* ctl_find (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_remove_ctl (struct snd_ac97*,char*,char*) ; 

__attribute__((used)) static int tune_hp_only(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", NULL);
	struct snd_kcontrol *mvol = ctl_find(ac97, "Master Playback Volume", NULL);
	if (! msw || ! mvol)
		return -ENOENT;
	msw->put = bind_hp_volsw_put;
	mvol->put = bind_hp_volsw_put;
	snd_ac97_remove_ctl(ac97, "Headphone Playback", "Switch");
	snd_ac97_remove_ctl(ac97, "Headphone Playback", "Volume");
	return 0;
}