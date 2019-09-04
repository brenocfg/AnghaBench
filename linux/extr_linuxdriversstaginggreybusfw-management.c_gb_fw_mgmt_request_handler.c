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
typedef  int u8 ;
struct gb_operation {int type; TYPE_2__* connection; } ;
struct TYPE_4__ {TYPE_1__* bundle; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GB_FW_MGMT_TYPE_BACKEND_FW_UPDATED 129 
#define  GB_FW_MGMT_TYPE_LOADED_FW 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int fw_mgmt_backend_fw_updated_operation (struct gb_operation*) ; 
 int fw_mgmt_interface_fw_loaded_operation (struct gb_operation*) ; 

int gb_fw_mgmt_request_handler(struct gb_operation *op)
{
	u8 type = op->type;

	switch (type) {
	case GB_FW_MGMT_TYPE_LOADED_FW:
		return fw_mgmt_interface_fw_loaded_operation(op);
	case GB_FW_MGMT_TYPE_BACKEND_FW_UPDATED:
		return fw_mgmt_backend_fw_updated_operation(op);
	default:
		dev_err(&op->connection->bundle->dev,
			"unsupported request: %u\n", type);
		return -EINVAL;
	}
}