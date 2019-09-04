#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_mixer_oss {struct snd_card* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  numid; } ;
struct snd_kcontrol {int (* info ) (struct snd_kcontrol*,struct snd_ctl_elem_info*) ;TYPE_1__ id; } ;
struct snd_ctl_elem_info {scalar_t__ count; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; } ;
struct slot {scalar_t__ channels; int present; int /*<<< orphan*/ * numid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_ctl_elem_info*) ; 
 struct snd_ctl_elem_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_mixer_oss_test_id (struct snd_mixer_oss*,char const*,int) ; 
 int stub1 (struct snd_kcontrol*,struct snd_ctl_elem_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_mixer_oss_build_test(struct snd_mixer_oss *mixer, struct slot *slot, const char *name, int index, int item)
{
	struct snd_ctl_elem_info *info;
	struct snd_kcontrol *kcontrol;
	struct snd_card *card = mixer->card;
	int err;

	down_read(&card->controls_rwsem);
	kcontrol = snd_mixer_oss_test_id(mixer, name, index);
	if (kcontrol == NULL) {
		up_read(&card->controls_rwsem);
		return 0;
	}
	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (! info) {
		up_read(&card->controls_rwsem);
		return -ENOMEM;
	}
	if ((err = kcontrol->info(kcontrol, info)) < 0) {
		up_read(&card->controls_rwsem);
		kfree(info);
		return err;
	}
	slot->numid[item] = kcontrol->id.numid;
	up_read(&card->controls_rwsem);
	if (info->count > slot->channels)
		slot->channels = info->count;
	slot->present |= 1 << item;
	kfree(info);
	return 0;
}