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
struct snd_ff {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_root; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int /*<<< orphan*/  add_node (struct snd_ff*,struct snd_info_entry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_dump_clock_config ; 
 int /*<<< orphan*/  proc_dump_sync_status ; 
 struct snd_info_entry* snd_info_create_card_entry (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_info_free_entry (struct snd_info_entry*) ; 
 scalar_t__ snd_info_register (struct snd_info_entry*) ; 

void snd_ff_proc_init(struct snd_ff *ff)
{
	struct snd_info_entry *root;

	/*
	 * All nodes are automatically removed at snd_card_disconnect(),
	 * by following to link list.
	 */
	root = snd_info_create_card_entry(ff->card, "firewire",
					  ff->card->proc_root);
	if (root == NULL)
		return;
	root->mode = S_IFDIR | 0555;
	if (snd_info_register(root) < 0) {
		snd_info_free_entry(root);
		return;
	}

	add_node(ff, root, "clock-config", proc_dump_clock_config);
	add_node(ff, root, "sync-status", proc_dump_sync_status);
}