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
struct net_bridge_fdb_entry {struct net_bridge_port const* dst; int /*<<< orphan*/  added_by_user; scalar_t__ is_local; } ;
struct net_bridge {int /*<<< orphan*/  hash_lock; } ;

/* Variables and functions */
 struct net_bridge_fdb_entry* br_fdb_find (struct net_bridge*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_delete_local (struct net_bridge*,struct net_bridge_port const*,struct net_bridge_fdb_entry*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void br_fdb_find_delete_local(struct net_bridge *br,
			      const struct net_bridge_port *p,
			      const unsigned char *addr, u16 vid)
{
	struct net_bridge_fdb_entry *f;

	spin_lock_bh(&br->hash_lock);
	f = br_fdb_find(br, addr, vid);
	if (f && f->is_local && !f->added_by_user && f->dst == p)
		fdb_delete_local(br, p, f);
	spin_unlock_bh(&br->hash_lock);
}