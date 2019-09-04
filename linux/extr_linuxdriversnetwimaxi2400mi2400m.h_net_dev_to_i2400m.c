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
struct net_device {int dummy; } ;
struct i2400m {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 struct i2400m* wimax_dev_to_i2400m (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct i2400m *net_dev_to_i2400m(struct net_device *net_dev)
{
	return wimax_dev_to_i2400m(netdev_priv(net_dev));
}