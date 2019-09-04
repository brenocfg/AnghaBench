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
struct gb_svc {int dummy; } ;
struct gb_interface {int /*<<< orphan*/  interface_id; TYPE_1__* hd; } ;
struct TYPE_2__ {struct gb_svc* svc; } ;

/* Variables and functions */
 int gb_svc_intf_set_power_mode_hibernate (struct gb_svc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gb_interface_hibernate_link(struct gb_interface *intf)
{
	struct gb_svc *svc = intf->hd->svc;

	return gb_svc_intf_set_power_mode_hibernate(svc, intf->interface_id);
}