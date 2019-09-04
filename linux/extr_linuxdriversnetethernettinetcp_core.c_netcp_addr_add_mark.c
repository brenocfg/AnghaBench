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
struct netcp_intf {int dummy; } ;
struct netcp_addr {int /*<<< orphan*/  flags; } ;
typedef  enum netcp_addr_type { ____Placeholder_netcp_addr_type } netcp_addr_type ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_NEW ; 
 int /*<<< orphan*/  ADDR_VALID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct netcp_addr* netcp_addr_add (struct netcp_intf*,int /*<<< orphan*/  const*,int) ; 
 struct netcp_addr* netcp_addr_find (struct netcp_intf*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void netcp_addr_add_mark(struct netcp_intf *netcp, const u8 *addr,
				enum netcp_addr_type type)
{
	struct netcp_addr *naddr;

	naddr = netcp_addr_find(netcp, addr, type);
	if (naddr) {
		naddr->flags |= ADDR_VALID;
		return;
	}

	naddr = netcp_addr_add(netcp, addr, type);
	if (!WARN_ON(!naddr))
		naddr->flags |= ADDR_NEW;
}