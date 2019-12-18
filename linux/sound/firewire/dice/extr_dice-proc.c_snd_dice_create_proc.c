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
struct snd_info_entry {int mode; } ;
struct snd_dice {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_root; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  add_node (struct snd_dice*,struct snd_info_entry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dice_proc_read ; 
 int /*<<< orphan*/  dice_proc_read_formation ; 
 struct snd_info_entry* snd_info_create_card_entry (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void snd_dice_create_proc(struct snd_dice *dice)
{
	struct snd_info_entry *root;

	/*
	 * All nodes are automatically removed at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(dice->card, "firewire",
					  dice->card->proc_root);
	if (!root)
		return;
	root->mode = S_IFDIR | 0555;

	add_node(dice, root, "dice", dice_proc_read);
	add_node(dice, root, "formation", dice_proc_read_formation);
}