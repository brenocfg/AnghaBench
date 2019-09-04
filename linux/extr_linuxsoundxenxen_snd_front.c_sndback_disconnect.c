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
struct xen_snd_front_info {int /*<<< orphan*/  xb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XenbusStateInitialising ; 
 int /*<<< orphan*/  xen_snd_drv_fini (struct xen_snd_front_info*) ; 
 int /*<<< orphan*/  xenbus_switch_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sndback_disconnect(struct xen_snd_front_info *front_info)
{
	xen_snd_drv_fini(front_info);
	xenbus_switch_state(front_info->xb_dev, XenbusStateInitialising);
}