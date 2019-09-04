#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct visor_segment_state {scalar_t__ alive; scalar_t__ operating; } ;
struct TYPE_11__ {scalar_t__ created; } ;
struct visor_device {struct controlvm_message_header* pending_msg_hdr; TYPE_2__ state; } ;
struct TYPE_10__ {struct visor_segment_state state; int /*<<< orphan*/  dev_no; int /*<<< orphan*/  bus_no; } ;
struct controlvm_message_packet {TYPE_1__ device_change_state; } ;
struct controlvm_message_header {int dummy; } ;
struct TYPE_13__ {int response_expected; } ;
struct TYPE_16__ {int /*<<< orphan*/  id; TYPE_4__ flags; } ;
struct controlvm_message {TYPE_7__ hdr; struct controlvm_message_packet cmd; } ;
struct TYPE_17__ {TYPE_3__* acpi_device; } ;
struct TYPE_15__ {scalar_t__ alive; scalar_t__ operating; } ;
struct TYPE_14__ {scalar_t__ alive; scalar_t__ operating; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_9__* chipset_dev ; 
 int /*<<< orphan*/  controlvm_responder (int /*<<< orphan*/ ,TYPE_7__*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct controlvm_message_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct controlvm_message_header*,TYPE_7__*,int) ; 
 TYPE_6__ segment_state_running ; 
 TYPE_5__ segment_state_standby ; 
 struct visor_device* visorbus_get_device_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int visorchipset_device_pause (struct visor_device*) ; 
 int visorchipset_device_resume (struct visor_device*) ; 

__attribute__((used)) static int visorbus_device_changestate(struct controlvm_message *inmsg)
{
	struct controlvm_message_packet *cmd = &inmsg->cmd;
	struct controlvm_message_header *pmsg_hdr;
	u32 bus_no = cmd->device_change_state.bus_no;
	u32 dev_no = cmd->device_change_state.dev_no;
	struct visor_segment_state state = cmd->device_change_state.state;
	struct visor_device *dev_info;
	int err = 0;

	dev_info = visorbus_get_device_by_id(bus_no, dev_no, NULL);
	if (!dev_info) {
		err = -ENODEV;
		goto err_respond;
	}
	if (dev_info->state.created == 0) {
		err = -EINVAL;
		goto err_respond;
	}
	if (dev_info->pending_msg_hdr) {
		/* only non-NULL if dev is still waiting on a response */
		err = -EIO;
		goto err_respond;
	}

	if (inmsg->hdr.flags.response_expected == 1) {
		pmsg_hdr = kzalloc(sizeof(*pmsg_hdr), GFP_KERNEL);
		if (!pmsg_hdr) {
			err = -ENOMEM;
			goto err_respond;
		}
		memcpy(pmsg_hdr, &inmsg->hdr,
		       sizeof(struct controlvm_message_header));
		dev_info->pending_msg_hdr = pmsg_hdr;
	}
	if (state.alive == segment_state_running.alive &&
	    state.operating == segment_state_running.operating)
		/* Response will be sent from visorchipset_device_resume */
		err = visorchipset_device_resume(dev_info);
	/* ServerNotReady / ServerLost / SegmentStateStandby */
	else if (state.alive == segment_state_standby.alive &&
		 state.operating == segment_state_standby.operating)
		/*
		 * technically this is standby case where server is lost.
		 * Response will be sent from visorchipset_device_pause.
		 */
		err = visorchipset_device_pause(dev_info);
	if (err)
		goto err_respond;
	return 0;

err_respond:
	dev_err(&chipset_dev->acpi_device->dev, "failed: %d\n", err);
	if (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	return err;
}