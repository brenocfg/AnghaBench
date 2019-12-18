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
struct snd_kcontrol {int /*<<< orphan*/  put; } ;
struct snd_ac97 {int /*<<< orphan*/  scaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_PD_EAPD ; 
 int /*<<< orphan*/  AC97_POWERDOWN ; 
 int /*<<< orphan*/  AC97_SCAP_EAPD_LED ; 
 int ENOENT ; 
 struct snd_kcontrol* ctl_find (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  master_mute_sw_put ; 
 int /*<<< orphan*/  snd_ac97_remove_ctl (struct snd_ac97*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ac97_update_bits (struct snd_ac97*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tune_mute_led(struct snd_ac97 *ac97)
{
	struct snd_kcontrol *msw = ctl_find(ac97, "Master Playback Switch", NULL);
	if (! msw)
		return -ENOENT;
	msw->put = master_mute_sw_put;
	snd_ac97_remove_ctl(ac97, "External Amplifier", NULL);
	snd_ac97_update_bits(
		ac97, AC97_POWERDOWN,
		AC97_PD_EAPD, AC97_PD_EAPD /* mute LED on */
	);
	ac97->scaps |= AC97_SCAP_EAPD_LED;
	return 0;
}