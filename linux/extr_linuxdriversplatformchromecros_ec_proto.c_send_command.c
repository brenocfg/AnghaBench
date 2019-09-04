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
struct ec_response_get_comms_status {int flags; } ;
struct cros_ec_device {int proto_version; int (* pkt_xfer ) (struct cros_ec_device*,struct cros_ec_command*) ;int (* cmd_xfer ) (struct cros_ec_device*,struct cros_ec_command*) ;} ;
struct cros_ec_command {scalar_t__ result; int insize; scalar_t__ data; scalar_t__ outsize; int /*<<< orphan*/  command; scalar_t__ version; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  EC_CMD_GET_COMMS_STATUS ; 
 int EC_COMMAND_RETRIES ; 
 int EC_COMMS_STATUS_PROCESSING ; 
 scalar_t__ EC_RES_IN_PROGRESS ; 
 scalar_t__ EC_RES_SUCCESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct cros_ec_command*) ; 
 struct cros_ec_command* kmalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cros_ec_device*,struct cros_ec_command*) ; 
 int stub2 (struct cros_ec_device*,struct cros_ec_command*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int send_command(struct cros_ec_device *ec_dev,
			struct cros_ec_command *msg)
{
	int ret;
	int (*xfer_fxn)(struct cros_ec_device *ec, struct cros_ec_command *msg);

	if (ec_dev->proto_version > 2)
		xfer_fxn = ec_dev->pkt_xfer;
	else
		xfer_fxn = ec_dev->cmd_xfer;

	ret = (*xfer_fxn)(ec_dev, msg);
	if (msg->result == EC_RES_IN_PROGRESS) {
		int i;
		struct cros_ec_command *status_msg;
		struct ec_response_get_comms_status *status;

		status_msg = kmalloc(sizeof(*status_msg) + sizeof(*status),
				     GFP_KERNEL);
		if (!status_msg)
			return -ENOMEM;

		status_msg->version = 0;
		status_msg->command = EC_CMD_GET_COMMS_STATUS;
		status_msg->insize = sizeof(*status);
		status_msg->outsize = 0;

		/*
		 * Query the EC's status until it's no longer busy or
		 * we encounter an error.
		 */
		for (i = 0; i < EC_COMMAND_RETRIES; i++) {
			usleep_range(10000, 11000);

			ret = (*xfer_fxn)(ec_dev, status_msg);
			if (ret == -EAGAIN)
				continue;
			if (ret < 0)
				break;

			msg->result = status_msg->result;
			if (status_msg->result != EC_RES_SUCCESS)
				break;

			status = (struct ec_response_get_comms_status *)
				 status_msg->data;
			if (!(status->flags & EC_COMMS_STATUS_PROCESSING))
				break;
		}

		kfree(status_msg);
	}

	return ret;
}