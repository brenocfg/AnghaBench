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
struct snd_kcontrol {int /*<<< orphan*/  info; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;
typedef  enum snd_ctl_add_mode { ____Placeholder_snd_ctl_add_mode } snd_ctl_add_mode ;

/* Variables and functions */
 int EINVAL ; 
 int __snd_ctl_add_replace (struct snd_card*,struct snd_kcontrol*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_ctl_free_one (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_ctl_add_replace(struct snd_card *card,
			       struct snd_kcontrol *kcontrol,
			       enum snd_ctl_add_mode mode)
{
	int err = -EINVAL;

	if (! kcontrol)
		return err;
	if (snd_BUG_ON(!card || !kcontrol->info))
		goto error;

	down_write(&card->controls_rwsem);
	err = __snd_ctl_add_replace(card, kcontrol, mode);
	up_write(&card->controls_rwsem);
	if (err < 0)
		goto error;
	return 0;

 error:
	snd_ctl_free_one(kcontrol);
	return err;
}