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
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_port {int dummy; } ;
struct net_bridge_fdb_entry {scalar_t__ added_by_external_learn; } ;
struct net_bridge {int /*<<< orphan*/  hash_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 struct net_bridge_fdb_entry* br_fdb_find (struct net_bridge*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_delete (struct net_bridge*,struct net_bridge_fdb_entry*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_fdb_external_learn_del(struct net_bridge *br, struct net_bridge_port *p,
			      const unsigned char *addr, u16 vid,
			      bool swdev_notify)
{
	struct net_bridge_fdb_entry *fdb;
	int err = 0;

	spin_lock_bh(&br->hash_lock);

	fdb = br_fdb_find(br, addr, vid);
	if (fdb && fdb->added_by_external_learn)
		fdb_delete(br, fdb, swdev_notify);
	else
		err = -ENOENT;

	spin_unlock_bh(&br->hash_lock);

	return err;
}