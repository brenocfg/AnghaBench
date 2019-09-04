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
struct gb_host_device {int /*<<< orphan*/  cport_id_map; int /*<<< orphan*/  bus_id; scalar_t__ svc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_hd_bus_id_map ; 
 int /*<<< orphan*/  gb_svc_put (scalar_t__) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gb_host_device*) ; 
 struct gb_host_device* to_gb_host_device (struct device*) ; 
 int /*<<< orphan*/  trace_gb_hd_release (struct gb_host_device*) ; 

__attribute__((used)) static void gb_hd_release(struct device *dev)
{
	struct gb_host_device *hd = to_gb_host_device(dev);

	trace_gb_hd_release(hd);

	if (hd->svc)
		gb_svc_put(hd->svc);
	ida_simple_remove(&gb_hd_bus_id_map, hd->bus_id);
	ida_destroy(&hd->cport_id_map);
	kfree(hd);
}