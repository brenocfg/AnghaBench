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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TABLE_LOCAL ; 
 unsigned int __inet_dev_addr_type (struct net*,struct net_device const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ l3mdev_fib_table (struct net_device const*) ; 

unsigned int inet_dev_addr_type(struct net *net, const struct net_device *dev,
				__be32 addr)
{
	u32 rt_table = l3mdev_fib_table(dev) ? : RT_TABLE_LOCAL;

	return __inet_dev_addr_type(net, dev, addr, rt_table);
}