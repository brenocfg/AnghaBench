#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {scalar_t__ created; } ;
struct visor_device {struct controlvm_message_header* pending_msg_hdr; TYPE_3__ state; } ;
struct controlvm_message_header {int dummy; } ;
struct TYPE_10__ {int response_expected; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; TYPE_4__ flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus_no; } ;
struct TYPE_8__ {TYPE_1__ destroy_bus; } ;
struct controlvm_message {TYPE_5__ hdr; TYPE_2__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ROOT_DEVICE ; 
 int EEXIST ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  controlvm_responder (int /*<<< orphan*/ ,TYPE_5__*,int) ; 
 struct controlvm_message_header* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct controlvm_message_header*,TYPE_5__*,int) ; 
 struct visor_device* visorbus_get_device_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  visorbus_remove_instance (struct visor_device*) ; 

__attribute__((used)) static int visorbus_destroy(struct controlvm_message *inmsg)
{
	struct controlvm_message_header *pmsg_hdr;
	u32 bus_no = inmsg->cmd.destroy_bus.bus_no;
	struct visor_device *bus_info;
	int err;

	bus_info = visorbus_get_device_by_id(bus_no, BUS_ROOT_DEVICE, NULL);
	if (!bus_info) {
		err = -ENODEV;
		goto err_respond;
	}
	if (bus_info->state.created == 0) {
		err = -ENOENT;
		goto err_respond;
	}
	if (bus_info->pending_msg_hdr) {
		/* only non-NULL if dev is still waiting on a response */
		err = -EEXIST;
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
		bus_info->pending_msg_hdr = pmsg_hdr;
	}
	/* Response will be handled by visorbus_remove_instance */
	visorbus_remove_instance(bus_info);
	return 0;

err_respond:
	if (inmsg->hdr.flags.response_expected == 1)
		controlvm_responder(inmsg->hdr.id, &inmsg->hdr, err);
	return err;
}