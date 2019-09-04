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
#define  GB_BOOTROM_TYPE_FIRMWARE_SIZE 130 
#define  GB_BOOTROM_TYPE_GET_FIRMWARE 129 
#define  GB_BOOTROM_TYPE_READY_TO_BOOT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int gb_bootrom_firmware_size_request (struct gb_operation*) ; 
 int gb_bootrom_get_firmware (struct gb_operation*) ; 
 int gb_bootrom_ready_to_boot (struct gb_operation*) ; 

__attribute__((used)) static int gb_bootrom_request_handler(struct gb_operation *op)
{
	u8 type = op->type;

	switch (type) {
	case GB_BOOTROM_TYPE_FIRMWARE_SIZE:
		return gb_bootrom_firmware_size_request(op);
	case GB_BOOTROM_TYPE_GET_FIRMWARE:
		return gb_bootrom_get_firmware(op);
	case GB_BOOTROM_TYPE_READY_TO_BOOT:
		return gb_bootrom_ready_to_boot(op);
	default:
		dev_err(&op->connection->bundle->dev,
			"unsupported request: %u\n", type);
		return -EINVAL;
	}
}