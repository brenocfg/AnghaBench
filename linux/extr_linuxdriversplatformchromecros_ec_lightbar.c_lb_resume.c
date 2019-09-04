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
struct cros_ec_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIGHTBAR_CMD_RESUME ; 
 struct cros_ec_dev* ec_with_lightbar ; 
 int lb_send_empty_cmd (struct cros_ec_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ userspace_control ; 

int lb_resume(struct cros_ec_dev *ec)
{
	if (userspace_control || ec != ec_with_lightbar)
		return 0;

	return lb_send_empty_cmd(ec, LIGHTBAR_CMD_RESUME);
}