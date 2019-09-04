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
struct cros_ec_device {int /*<<< orphan*/  dev; } ;
struct cros_ec_command {int result; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int EAGAIN ; 
#define  EC_RES_IN_PROGRESS 129 
#define  EC_RES_SUCCESS 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

int cros_ec_check_result(struct cros_ec_device *ec_dev,
			 struct cros_ec_command *msg)
{
	switch (msg->result) {
	case EC_RES_SUCCESS:
		return 0;
	case EC_RES_IN_PROGRESS:
		dev_dbg(ec_dev->dev, "command 0x%02x in progress\n",
			msg->command);
		return -EAGAIN;
	default:
		dev_dbg(ec_dev->dev, "command 0x%02x returned %d\n",
			msg->command, msg->result);
		return 0;
	}
}