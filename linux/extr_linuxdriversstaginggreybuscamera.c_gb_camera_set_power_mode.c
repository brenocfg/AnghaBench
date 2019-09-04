#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gb_svc {int /*<<< orphan*/  ap_intf_id; } ;
struct gb_interface {int /*<<< orphan*/  interface_id; } ;
struct gb_camera {TYPE_2__* connection; } ;
struct TYPE_4__ {TYPE_1__* hd; struct gb_interface* intf; } ;
struct TYPE_3__ {struct gb_svc* svc; } ;

/* Variables and functions */
 int gb_camera_set_intf_power_mode (struct gb_camera*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcam_err (struct gb_camera*,char*,char*,int) ; 

__attribute__((used)) static int gb_camera_set_power_mode(struct gb_camera *gcam, bool hs)
{
	struct gb_interface *intf = gcam->connection->intf;
	struct gb_svc *svc = gcam->connection->hd->svc;
	int ret;

	ret = gb_camera_set_intf_power_mode(gcam, intf->interface_id, hs);
	if (ret < 0) {
		gcam_err(gcam, "failed to set module interface to %s (%d)\n",
			 hs ? "HS" : "PWM", ret);
		return ret;
	}

	ret = gb_camera_set_intf_power_mode(gcam, svc->ap_intf_id, hs);
	if (ret < 0) {
		gb_camera_set_intf_power_mode(gcam, intf->interface_id, !hs);
		gcam_err(gcam, "failed to set AP interface to %s (%d)\n",
			 hs ? "HS" : "PWM", ret);
		return ret;
	}

	return 0;
}