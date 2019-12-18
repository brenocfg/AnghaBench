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
struct net {int dummy; } ;
struct mr_table {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct net_device *ipmr_reg_vif(struct net *net, struct mr_table *mrt)
{
	return NULL;
}