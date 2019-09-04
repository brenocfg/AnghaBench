#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_interface {int quirks; void* product_id; void* vendor_id; } ;
struct gb_connection {TYPE_1__* bundle; } ;
struct gb_bootrom_get_vid_pid_response {int /*<<< orphan*/  product_id; int /*<<< orphan*/  vendor_id; } ;
struct gb_bootrom {struct gb_connection* connection; } ;
typedef  int /*<<< orphan*/  response ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct gb_interface* intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_BOOTROM_TYPE_GET_VID_PID ; 
 int GB_INTERFACE_QUIRK_NO_GMP_IDS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,void*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gb_bootrom_get_vid_pid_response*,int) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bootrom_es2_fixup_vid_pid(struct gb_bootrom *bootrom)
{
	struct gb_bootrom_get_vid_pid_response response;
	struct gb_connection *connection = bootrom->connection;
	struct gb_interface *intf = connection->bundle->intf;
	int ret;

	if (!(intf->quirks & GB_INTERFACE_QUIRK_NO_GMP_IDS))
		return;

	ret = gb_operation_sync(connection, GB_BOOTROM_TYPE_GET_VID_PID,
				NULL, 0, &response, sizeof(response));
	if (ret) {
		dev_err(&connection->bundle->dev,
			"Bootrom get vid/pid operation failed (%d)\n", ret);
		return;
	}

	/*
	 * NOTE: This is hacked, so that the same values of VID/PID can be used
	 * by next firmware level as well. The uevent for bootrom will still
	 * have VID/PID as 0, though after this point the sysfs files will start
	 * showing the updated values. But yeah, that's a bit racy as the same
	 * sysfs files would be showing 0 before this point.
	 */
	intf->vendor_id = le32_to_cpu(response.vendor_id);
	intf->product_id = le32_to_cpu(response.product_id);

	dev_dbg(&connection->bundle->dev, "Bootrom got vid (0x%x)/pid (0x%x)\n",
		intf->vendor_id, intf->product_id);
}