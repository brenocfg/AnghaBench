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
struct net_device {scalar_t__ dev_addr; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int __ipv6_isatap_ifid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int addrconf_ifid_gre(u8 *eui, struct net_device *dev)
{
	return __ipv6_isatap_ifid(eui, *(__be32 *)dev->dev_addr);
}