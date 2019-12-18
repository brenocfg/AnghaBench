#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * prev; } ;
struct TYPE_4__ {int mount_pending; TYPE_2__ list; int /*<<< orphan*/  no_list; int /*<<< orphan*/  devname; int /*<<< orphan*/  fs_id; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOSSIP_SUPER_DEBUG ; 
 TYPE_1__* ORANGEFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  __list_del_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_anon_super (struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  orangefs_request_mutex ; 
 int /*<<< orphan*/  orangefs_superblocks_lock ; 
 int orangefs_unmount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void orangefs_kill_sb(struct super_block *sb)
{
	int r;
	gossip_debug(GOSSIP_SUPER_DEBUG, "orangefs_kill_sb: called\n");

	/* provided sb cleanup */
	kill_anon_super(sb);

	if (!ORANGEFS_SB(sb)) {
		mutex_lock(&orangefs_request_mutex);
		mutex_unlock(&orangefs_request_mutex);
		return;
	}
	/*
	 * issue the unmount to userspace to tell it to remove the
	 * dynamic mount info it has for this superblock
	 */
	r = orangefs_unmount(ORANGEFS_SB(sb)->id, ORANGEFS_SB(sb)->fs_id,
	    ORANGEFS_SB(sb)->devname);
	if (!r)
		ORANGEFS_SB(sb)->mount_pending = 1;

	if (!ORANGEFS_SB(sb)->no_list) {
		/* remove the sb from our list of orangefs specific sb's */
		spin_lock(&orangefs_superblocks_lock);
		/* not list_del_init */
		__list_del_entry(&ORANGEFS_SB(sb)->list);
		ORANGEFS_SB(sb)->list.prev = NULL;
		spin_unlock(&orangefs_superblocks_lock);
	}

	/*
	 * make sure that ORANGEFS_DEV_REMOUNT_ALL loop that might've seen us
	 * gets completed before we free the dang thing.
	 */
	mutex_lock(&orangefs_request_mutex);
	mutex_unlock(&orangefs_request_mutex);

	/* free the orangefs superblock private data */
	kfree(ORANGEFS_SB(sb));
}