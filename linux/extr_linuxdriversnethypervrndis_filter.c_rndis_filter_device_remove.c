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
struct rndis_device {int dummy; } ;
struct netvsc_device {struct rndis_device* extension; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netvsc_device_remove (struct hv_device*) ; 
 int /*<<< orphan*/  rndis_filter_halt_device (struct netvsc_device*,struct rndis_device*) ; 

void rndis_filter_device_remove(struct hv_device *dev,
				struct netvsc_device *net_dev)
{
	struct rndis_device *rndis_dev = net_dev->extension;

	/* Halt and release the rndis device */
	rndis_filter_halt_device(net_dev, rndis_dev);

	net_dev->extension = NULL;

	netvsc_device_remove(dev);
}