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
struct snd_efw {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_root; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  add_node (struct snd_efw*,struct snd_info_entry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_read_clock ; 
 int /*<<< orphan*/  proc_read_hwinfo ; 
 int /*<<< orphan*/  proc_read_phys_meters ; 
 int /*<<< orphan*/  proc_read_queues_state ; 
 struct snd_info_entry* snd_info_create_card_entry (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

void snd_efw_proc_init(struct snd_efw *efw)
{
	struct snd_info_entry *root;

	/*
	 * All nodes are automatically removed at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(efw->card, "firewire",
					  efw->card->proc_root);
	if (root == NULL)
		return;
	root->mode = S_IFDIR | 0555;

	add_node(efw, root, "clock", proc_read_clock);
	add_node(efw, root, "firmware", proc_read_hwinfo);
	add_node(efw, root, "meters", proc_read_phys_meters);
	add_node(efw, root, "queues", proc_read_queues_state);
}