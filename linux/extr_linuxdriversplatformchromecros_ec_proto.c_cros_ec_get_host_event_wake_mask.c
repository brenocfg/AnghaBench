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
typedef  int /*<<< orphan*/  uint32_t ;
struct ec_response_host_event_mask {int /*<<< orphan*/  mask; } ;
struct cros_ec_device {int dummy; } ;
struct cros_ec_command {int insize; scalar_t__ data; scalar_t__ outsize; scalar_t__ version; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_HOST_EVENT_GET_WAKE_MASK ; 
 int send_command (struct cros_ec_device*,struct cros_ec_command*) ; 

__attribute__((used)) static int cros_ec_get_host_event_wake_mask(struct cros_ec_device *ec_dev,
					    struct cros_ec_command *msg,
					    uint32_t *mask)
{
	struct ec_response_host_event_mask *r;
	int ret;

	msg->command = EC_CMD_HOST_EVENT_GET_WAKE_MASK;
	msg->version = 0;
	msg->outsize = 0;
	msg->insize = sizeof(*r);

	ret = send_command(ec_dev, msg);
	if (ret > 0) {
		r = (struct ec_response_host_event_mask *)msg->data;
		*mask = r->mask;
	}

	return ret;
}