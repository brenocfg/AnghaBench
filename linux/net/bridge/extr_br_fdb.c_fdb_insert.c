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
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_port {TYPE_1__* dev; } ;
struct net_bridge_fdb_entry {scalar_t__ is_local; } ;
struct net_bridge {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  RTM_NEWNEIGH ; 
 struct net_bridge_fdb_entry* br_fdb_find (struct net_bridge*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_warn (struct net_bridge*,char*,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdb_add_hw_addr (struct net_bridge*,unsigned char const*) ; 
 struct net_bridge_fdb_entry* fdb_create (struct net_bridge*,struct net_bridge_port*,unsigned char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fdb_delete (struct net_bridge*,struct net_bridge_fdb_entry*,int) ; 
 int /*<<< orphan*/  fdb_notify (struct net_bridge*,struct net_bridge_fdb_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_valid_ether_addr (unsigned char const*) ; 

__attribute__((used)) static int fdb_insert(struct net_bridge *br, struct net_bridge_port *source,
		  const unsigned char *addr, u16 vid)
{
	struct net_bridge_fdb_entry *fdb;

	if (!is_valid_ether_addr(addr))
		return -EINVAL;

	fdb = br_fdb_find(br, addr, vid);
	if (fdb) {
		/* it is okay to have multiple ports with same
		 * address, just use the first one.
		 */
		if (fdb->is_local)
			return 0;
		br_warn(br, "adding interface %s with same address as a received packet (addr:%pM, vlan:%u)\n",
		       source ? source->dev->name : br->dev->name, addr, vid);
		fdb_delete(br, fdb, true);
	}

	fdb = fdb_create(br, source, addr, vid, 1, 1);
	if (!fdb)
		return -ENOMEM;

	fdb_add_hw_addr(br, addr);
	fdb_notify(br, fdb, RTM_NEWNEIGH, true);
	return 0;
}