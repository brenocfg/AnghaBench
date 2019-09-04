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
struct snd_card_aica {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_aica_pcmswitch_control ; 
 int /*<<< orphan*/  snd_aica_pcmvolume_control ; 
 int snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_card_aica*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int add_aicamixer_controls(struct snd_card_aica *dreamcastcard)
{
	int err;
	err = snd_ctl_add
	    (dreamcastcard->card,
	     snd_ctl_new1(&snd_aica_pcmvolume_control, dreamcastcard));
	if (unlikely(err < 0))
		return err;
	err = snd_ctl_add
	    (dreamcastcard->card,
	     snd_ctl_new1(&snd_aica_pcmswitch_control, dreamcastcard));
	if (unlikely(err < 0))
		return err;
	return 0;
}