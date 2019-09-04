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
struct gb_host_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_svc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_hd_del (struct gb_host_device*) ; 

void gb_hd_del(struct gb_host_device *hd)
{
	trace_gb_hd_del(hd);

	/*
	 * Tear down the svc and flush any on-going hotplug processing before
	 * removing the remaining interfaces.
	 */
	gb_svc_del(hd->svc);

	device_del(&hd->dev);
}