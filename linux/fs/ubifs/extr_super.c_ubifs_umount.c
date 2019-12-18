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
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {int /*<<< orphan*/  bottom_up_buf; int /*<<< orphan*/  sbuf; int /*<<< orphan*/  ileb_buf; TYPE_2__ bu; int /*<<< orphan*/  write_reserve_buf; int /*<<< orphan*/  mst_node; int /*<<< orphan*/  rcvrd_mst_node; int /*<<< orphan*/  cbuf; int /*<<< orphan*/  auth_hash_name; int /*<<< orphan*/  auth_key_name; scalar_t__ bgt; int /*<<< orphan*/  infos_list; TYPE_1__ vi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_debugfs_exit_fs (struct ubifs_info*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_journal (struct ubifs_info*) ; 
 int /*<<< orphan*/  free_orphans (struct ubifs_info*) ; 
 int /*<<< orphan*/  free_wbufs (struct ubifs_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_debugging_exit (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_exit_authentication (struct ubifs_info*) ; 
 int /*<<< orphan*/  ubifs_infos_lock ; 
 int /*<<< orphan*/  ubifs_lpt_free (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ubifs_umount(struct ubifs_info *c)
{
	dbg_gen("un-mounting UBI device %d, volume %d", c->vi.ubi_num,
		c->vi.vol_id);

	dbg_debugfs_exit_fs(c);
	spin_lock(&ubifs_infos_lock);
	list_del(&c->infos_list);
	spin_unlock(&ubifs_infos_lock);

	if (c->bgt)
		kthread_stop(c->bgt);

	destroy_journal(c);
	free_wbufs(c);
	free_orphans(c);
	ubifs_lpt_free(c, 0);
	ubifs_exit_authentication(c);

	kfree(c->auth_key_name);
	kfree(c->auth_hash_name);
	kfree(c->cbuf);
	kfree(c->rcvrd_mst_node);
	kfree(c->mst_node);
	kfree(c->write_reserve_buf);
	kfree(c->bu.buf);
	vfree(c->ileb_buf);
	vfree(c->sbuf);
	kfree(c->bottom_up_buf);
	ubifs_debugging_exit(c);
}