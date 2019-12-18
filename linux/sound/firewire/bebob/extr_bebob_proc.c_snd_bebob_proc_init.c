#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_info_entry {int mode; } ;
struct snd_bebob {TYPE_1__* spec; TYPE_2__* card; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc_root; } ;
struct TYPE_3__ {int /*<<< orphan*/ * meter; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  add_node (struct snd_bebob*,struct snd_info_entry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_read_clock ; 
 int /*<<< orphan*/  proc_read_formation ; 
 int /*<<< orphan*/  proc_read_hw_info ; 
 int /*<<< orphan*/  proc_read_meters ; 
 struct snd_info_entry* snd_info_create_card_entry (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

void snd_bebob_proc_init(struct snd_bebob *bebob)
{
	struct snd_info_entry *root;

	/*
	 * All nodes are automatically removed at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(bebob->card, "firewire",
					  bebob->card->proc_root);
	if (root == NULL)
		return;
	root->mode = S_IFDIR | 0555;

	add_node(bebob, root, "clock", proc_read_clock);
	add_node(bebob, root, "firmware", proc_read_hw_info);
	add_node(bebob, root, "formation", proc_read_formation);

	if (bebob->spec->meter != NULL)
		add_node(bebob, root, "meter", proc_read_meters);
}