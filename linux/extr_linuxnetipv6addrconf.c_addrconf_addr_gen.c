#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int addr_gen_mode; } ;
struct inet6_dev {int /*<<< orphan*/  dev; TYPE_1__ cnf; } ;
struct in6_addr {int /*<<< orphan*/  s6_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IFA_F_STABLE_PRIVACY ; 
#define  IN6_ADDR_GEN_MODE_EUI64 131 
#define  IN6_ADDR_GEN_MODE_NONE 130 
#define  IN6_ADDR_GEN_MODE_RANDOM 129 
#define  IN6_ADDR_GEN_MODE_STABLE_PRIVACY 128 
 int /*<<< orphan*/  addrconf_add_linklocal (struct inet6_dev*,struct in6_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addrconf_prefix_route (struct in6_addr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  ipv6_addr_set (struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_gen_mode_random_init (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_generate_eui64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_generate_stable_address (struct in6_addr*,int /*<<< orphan*/ ,struct inet6_dev*) ; 
 scalar_t__ netif_is_l3_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addrconf_addr_gen(struct inet6_dev *idev, bool prefix_route)
{
	struct in6_addr addr;

	/* no link local addresses on L3 master devices */
	if (netif_is_l3_master(idev->dev))
		return;

	ipv6_addr_set(&addr, htonl(0xFE800000), 0, 0, 0);

	switch (idev->cnf.addr_gen_mode) {
	case IN6_ADDR_GEN_MODE_RANDOM:
		ipv6_gen_mode_random_init(idev);
		/* fallthrough */
	case IN6_ADDR_GEN_MODE_STABLE_PRIVACY:
		if (!ipv6_generate_stable_address(&addr, 0, idev))
			addrconf_add_linklocal(idev, &addr,
					       IFA_F_STABLE_PRIVACY);
		else if (prefix_route)
			addrconf_prefix_route(&addr, 64, 0, idev->dev,
					      0, 0, GFP_KERNEL);
		break;
	case IN6_ADDR_GEN_MODE_EUI64:
		/* addrconf_add_linklocal also adds a prefix_route and we
		 * only need to care about prefix routes if ipv6_generate_eui64
		 * couldn't generate one.
		 */
		if (ipv6_generate_eui64(addr.s6_addr + 8, idev->dev) == 0)
			addrconf_add_linklocal(idev, &addr, 0);
		else if (prefix_route)
			addrconf_prefix_route(&addr, 64, 0, idev->dev,
					      0, 0, GFP_KERNEL);
		break;
	case IN6_ADDR_GEN_MODE_NONE:
	default:
		/* will not add any link local address */
		break;
	}
}