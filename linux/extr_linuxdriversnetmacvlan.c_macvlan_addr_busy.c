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
struct macvlan_port {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  macvlan_addr_change (struct macvlan_port const*) ; 
 scalar_t__ macvlan_hash_lookup (struct macvlan_port const*,unsigned char const*) ; 
 int /*<<< orphan*/  macvlan_passthru (struct macvlan_port const*) ; 

__attribute__((used)) static bool macvlan_addr_busy(const struct macvlan_port *port,
			      const unsigned char *addr)
{
	/* Test to see if the specified address is
	 * currently in use by the underlying device or
	 * another macvlan.
	 */
	if (!macvlan_passthru(port) && !macvlan_addr_change(port) &&
	    ether_addr_equal_64bits(port->dev->dev_addr, addr))
		return true;

	if (macvlan_hash_lookup(port, addr))
		return true;

	return false;
}