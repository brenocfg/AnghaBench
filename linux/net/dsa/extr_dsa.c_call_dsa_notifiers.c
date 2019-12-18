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
struct dsa_notifier_info {struct net_device* dev; } ;

/* Variables and functions */
 int atomic_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,struct dsa_notifier_info*) ; 
 int /*<<< orphan*/  dsa_notif_chain ; 

int call_dsa_notifiers(unsigned long val, struct net_device *dev,
		       struct dsa_notifier_info *info)
{
	info->dev = dev;
	return atomic_notifier_call_chain(&dsa_notif_chain, val, info);
}