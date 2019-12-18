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
struct snd_kcontrol {int dummy; } ;
struct snd_ac97 {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct snd_kcontrol* ctl_find (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_inv_eapd (struct snd_ac97*,struct snd_kcontrol*) ; 

__attribute__((used)) static int tune_inv_eapd(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *kctl = ctl_find(ac97, "External Amplifier", NULL);
	if (! kctl)
		return -ENOENT;
	set_inv_eapd(ac97, kctl);
	return 0;
}