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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_port {int dummy; } ;
struct net_bridge_fdb_entry {struct net_bridge_port const* dst; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct net_bridge_fdb_entry* br_fdb_find (struct net_bridge*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_delete (struct net_bridge*,struct net_bridge_fdb_entry*,int) ; 

__attribute__((used)) static int fdb_delete_by_addr_and_port(struct net_bridge *br,
				       const struct net_bridge_port *p,
				       const u8 *addr, u16 vlan)
{
	struct net_bridge_fdb_entry *fdb;

	fdb = br_fdb_find(br, addr, vlan);
	if (!fdb || fdb->dst != p)
		return -ENOENT;

	fdb_delete(br, fdb, true);

	return 0;
}