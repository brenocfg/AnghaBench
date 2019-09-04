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
struct vstor_packet {scalar_t__ operation; scalar_t__ status; int /*<<< orphan*/  flags; } ;
struct storvsc_cmd_request {int /*<<< orphan*/  wait_event; struct vstor_packet vstor_packet; } ;
struct hv_device {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  REQUEST_COMPLETION_FLAG ; 
 int /*<<< orphan*/  VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 scalar_t__ VSTOR_OPERATION_COMPLETE_IO ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int vmbus_sendpacket (int /*<<< orphan*/ ,struct vstor_packet*,scalar_t__,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmscsi_size_delta ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int storvsc_execute_vstor_op(struct hv_device *device,
				    struct storvsc_cmd_request *request,
				    bool status_check)
{
	struct vstor_packet *vstor_packet;
	int ret, t;

	vstor_packet = &request->vstor_packet;

	init_completion(&request->wait_event);
	vstor_packet->flags = REQUEST_COMPLETION_FLAG;

	ret = vmbus_sendpacket(device->channel, vstor_packet,
			       (sizeof(struct vstor_packet) -
			       vmscsi_size_delta),
			       (unsigned long)request,
			       VM_PKT_DATA_INBAND,
			       VMBUS_DATA_PACKET_FLAG_COMPLETION_REQUESTED);
	if (ret != 0)
		return ret;

	t = wait_for_completion_timeout(&request->wait_event, 5*HZ);
	if (t == 0)
		return -ETIMEDOUT;

	if (!status_check)
		return ret;

	if (vstor_packet->operation != VSTOR_OPERATION_COMPLETE_IO ||
	    vstor_packet->status != 0)
		return -EINVAL;

	return ret;
}