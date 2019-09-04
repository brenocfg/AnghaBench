#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct visor_segment_state {int dummy; } ;
struct controlvm_message_header {int dummy; } ;
struct TYPE_9__ {int phys_device; } ;
struct TYPE_10__ {TYPE_3__ flags; struct visor_segment_state state; } ;
struct TYPE_11__ {TYPE_4__ device_change_state; } ;
struct TYPE_7__ {int test_message; } ;
struct TYPE_8__ {TYPE_1__ flags; } ;
struct controlvm_message {TYPE_5__ cmd; TYPE_2__ hdr; } ;
struct TYPE_12__ {int /*<<< orphan*/  controlvm_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROLVM_QUEUE_REQUEST ; 
 int EINVAL ; 
 TYPE_6__* chipset_dev ; 
 int /*<<< orphan*/  controlvm_init_response (struct controlvm_message*,struct controlvm_message_header*,int) ; 
 int visorchannel_signalinsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct controlvm_message*) ; 

__attribute__((used)) static int controlvm_respond(struct controlvm_message_header *msg_hdr,
			     int response, struct visor_segment_state *state)
{
	struct controlvm_message outmsg;

	controlvm_init_response(&outmsg, msg_hdr, response);
	if (outmsg.hdr.flags.test_message == 1)
		return -EINVAL;
	if (state) {
		outmsg.cmd.device_change_state.state = *state;
		outmsg.cmd.device_change_state.flags.phys_device = 1;
	}
	return visorchannel_signalinsert(chipset_dev->controlvm_channel,
					 CONTROLVM_QUEUE_REQUEST, &outmsg);
}