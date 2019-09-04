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
struct macvlan_source_entry {int /*<<< orphan*/  hlist; struct macvlan_dev* vlan; int /*<<< orphan*/  addr; } ;
struct macvlan_port {struct hlist_head* vlan_source_hash; } ;
struct macvlan_dev {int /*<<< orphan*/  macaddr_count; struct macvlan_port* port; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct macvlan_source_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 size_t macvlan_eth_hash (unsigned char const*) ; 
 struct macvlan_source_entry* macvlan_hash_lookup_source (struct macvlan_dev*,unsigned char const*) ; 

__attribute__((used)) static int macvlan_hash_add_source(struct macvlan_dev *vlan,
				   const unsigned char *addr)
{
	struct macvlan_port *port = vlan->port;
	struct macvlan_source_entry *entry;
	struct hlist_head *h;

	entry = macvlan_hash_lookup_source(vlan, addr);
	if (entry)
		return 0;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	ether_addr_copy(entry->addr, addr);
	entry->vlan = vlan;
	h = &port->vlan_source_hash[macvlan_eth_hash(addr)];
	hlist_add_head_rcu(&entry->hlist, h);
	vlan->macaddr_count++;

	return 0;
}