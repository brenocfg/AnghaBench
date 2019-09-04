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
struct net_device {int dummy; } ;
struct lowpan_btle_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 TYPE_1__* lowpan_dev (struct net_device const*) ; 

__attribute__((used)) static inline struct lowpan_btle_dev *
lowpan_btle_dev(const struct net_device *netdev)
{
	return (struct lowpan_btle_dev *)lowpan_dev(netdev)->priv;
}