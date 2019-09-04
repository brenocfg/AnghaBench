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
struct net_bridge_fdb_entry {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  fdb_hash_tbl; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 struct net_bridge_fdb_entry* fdb_find_rcu (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 

struct net_bridge_fdb_entry *br_fdb_find_rcu(struct net_bridge *br,
					     const unsigned char *addr,
					     __u16 vid)
{
	return fdb_find_rcu(&br->fdb_hash_tbl, addr, vid);
}