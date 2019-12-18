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
struct net_bridge_port {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_id; TYPE_1__ addr; } ;
struct net_bridge_fdb_entry {unsigned char is_local; unsigned char is_static; int /*<<< orphan*/  fdb_node; int /*<<< orphan*/  rhnode; int /*<<< orphan*/  used; int /*<<< orphan*/  updated; scalar_t__ is_sticky; scalar_t__ offloaded; scalar_t__ added_by_external_learn; scalar_t__ added_by_user; TYPE_2__ key; struct net_bridge_port* dst; } ;
struct net_bridge {int /*<<< orphan*/  fdb_list; int /*<<< orphan*/  fdb_hash_tbl; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  br_fdb_cache ; 
 int /*<<< orphan*/  br_fdb_rht_params ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct net_bridge_fdb_entry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct net_bridge_fdb_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ rhashtable_lookup_insert_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_bridge_fdb_entry *fdb_create(struct net_bridge *br,
					       struct net_bridge_port *source,
					       const unsigned char *addr,
					       __u16 vid,
					       unsigned char is_local,
					       unsigned char is_static)
{
	struct net_bridge_fdb_entry *fdb;

	fdb = kmem_cache_alloc(br_fdb_cache, GFP_ATOMIC);
	if (fdb) {
		memcpy(fdb->key.addr.addr, addr, ETH_ALEN);
		fdb->dst = source;
		fdb->key.vlan_id = vid;
		fdb->is_local = is_local;
		fdb->is_static = is_static;
		fdb->added_by_user = 0;
		fdb->added_by_external_learn = 0;
		fdb->offloaded = 0;
		fdb->is_sticky = 0;
		fdb->updated = fdb->used = jiffies;
		if (rhashtable_lookup_insert_fast(&br->fdb_hash_tbl,
						  &fdb->rhnode,
						  br_fdb_rht_params)) {
			kmem_cache_free(br_fdb_cache, fdb);
			fdb = NULL;
		} else {
			hlist_add_head_rcu(&fdb->fdb_node, &br->fdb_list);
		}
	}
	return fdb;
}