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
struct snd_ctl_elem_id {scalar_t__ numid; } ;
struct snd_kcontrol {scalar_t__ count; struct snd_ctl_elem_id id; } ;
struct snd_card {int /*<<< orphan*/  controls_rwsem; scalar_t__ last_numid; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 struct snd_kcontrol* snd_ctl_find_id (struct snd_card*,struct snd_ctl_elem_id*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int snd_ctl_rename_id(struct snd_card *card, struct snd_ctl_elem_id *src_id,
		      struct snd_ctl_elem_id *dst_id)
{
	struct snd_kcontrol *kctl;

	down_write(&card->controls_rwsem);
	kctl = snd_ctl_find_id(card, src_id);
	if (kctl == NULL) {
		up_write(&card->controls_rwsem);
		return -ENOENT;
	}
	kctl->id = *dst_id;
	kctl->id.numid = card->last_numid + 1;
	card->last_numid += kctl->count;
	up_write(&card->controls_rwsem);
	return 0;
}