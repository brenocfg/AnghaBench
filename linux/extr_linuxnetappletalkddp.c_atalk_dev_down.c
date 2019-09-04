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

/* Variables and functions */
 int /*<<< orphan*/  aarp_device_down (struct net_device*) ; 
 int /*<<< orphan*/  atif_drop_device (struct net_device*) ; 
 int /*<<< orphan*/  atrtr_device_down (struct net_device*) ; 

__attribute__((used)) static inline void atalk_dev_down(struct net_device *dev)
{
	atrtr_device_down(dev);	/* Remove all routes for the device */
	aarp_device_down(dev);	/* Remove AARP entries for the device */
	atif_drop_device(dev);	/* Remove the device */
}