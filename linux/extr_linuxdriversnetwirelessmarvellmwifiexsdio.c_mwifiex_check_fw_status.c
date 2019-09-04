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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRMWARE_READY_SDIO ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mwifiex_sdio_read_fw_status (struct mwifiex_adapter*,scalar_t__*) ; 

__attribute__((used)) static int mwifiex_check_fw_status(struct mwifiex_adapter *adapter,
				   u32 poll_num)
{
	int ret = 0;
	u16 firmware_stat;
	u32 tries;

	for (tries = 0; tries < poll_num; tries++) {
		ret = mwifiex_sdio_read_fw_status(adapter, &firmware_stat);
		if (ret)
			continue;
		if (firmware_stat == FIRMWARE_READY_SDIO) {
			ret = 0;
			break;
		}

		msleep(100);
		ret = -1;
	}

	return ret;
}