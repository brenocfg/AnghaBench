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
struct netcp_intf {int /*<<< orphan*/  addr_list; int /*<<< orphan*/  dev; } ;
struct netcp_addr {int type; int /*<<< orphan*/  node; int /*<<< orphan*/  addr; struct netcp_intf* netcp; scalar_t__ flags; } ;
typedef  enum netcp_addr_type { ____Placeholder_netcp_addr_type } netcp_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct netcp_addr* devm_kmalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct netcp_addr *netcp_addr_add(struct netcp_intf *netcp,
					 const u8 *addr,
					 enum netcp_addr_type type)
{
	struct netcp_addr *naddr;

	naddr = devm_kmalloc(netcp->dev, sizeof(*naddr), GFP_ATOMIC);
	if (!naddr)
		return NULL;

	naddr->type = type;
	naddr->flags = 0;
	naddr->netcp = netcp;
	if (addr)
		ether_addr_copy(naddr->addr, addr);
	else
		eth_zero_addr(naddr->addr);
	list_add_tail(&naddr->node, &netcp->addr_list);

	return naddr;
}