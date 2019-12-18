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
struct neigh_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __neigh_ifdown (struct neigh_table*,struct net_device*,int) ; 

int neigh_ifdown(struct neigh_table *tbl, struct net_device *dev)
{
	__neigh_ifdown(tbl, dev, false);
	return 0;
}