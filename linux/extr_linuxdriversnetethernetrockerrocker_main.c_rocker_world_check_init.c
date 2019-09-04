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
typedef  scalar_t__ u8 ;
struct rocker_port {struct rocker* rocker; } ;
struct rocker {TYPE_1__* pdev; TYPE_2__* wops; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int rocker_cmd_get_port_settings_mode (struct rocker_port*,scalar_t__*) ; 
 int rocker_world_init (struct rocker*,scalar_t__) ; 

__attribute__((used)) static int rocker_world_check_init(struct rocker_port *rocker_port)
{
	struct rocker *rocker = rocker_port->rocker;
	u8 mode;
	int err;

	err = rocker_cmd_get_port_settings_mode(rocker_port, &mode);
	if (err) {
		dev_err(&rocker->pdev->dev, "failed to get port mode\n");
		return err;
	}
	if (rocker->wops) {
		if (rocker->wops->mode != mode) {
			dev_err(&rocker->pdev->dev, "hardware has ports in different worlds, which is not supported\n");
			return -EINVAL;
		}
		return 0;
	}
	return rocker_world_init(rocker, mode);
}