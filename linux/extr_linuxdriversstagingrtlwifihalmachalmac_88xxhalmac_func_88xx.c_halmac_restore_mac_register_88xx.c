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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct halmac_restore_info {scalar_t__ mac_register; scalar_t__ value; int length; } ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; } ;

/* Variables and functions */
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_32 (struct halmac_adapter*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 

void halmac_restore_mac_register_88xx(struct halmac_adapter *halmac_adapter,
				      struct halmac_restore_info *restore_info,
				      u32 restore_num)
{
	u8 value_length;
	u32 i;
	u32 mac_register;
	u32 mac_value;
	struct halmac_api *halmac_api;
	struct halmac_restore_info *curr_restore_info = restore_info;

	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	for (i = 0; i < restore_num; i++) {
		mac_register = curr_restore_info->mac_register;
		mac_value = curr_restore_info->value;
		value_length = curr_restore_info->length;

		if (value_length == 1)
			HALMAC_REG_WRITE_8(halmac_adapter, mac_register,
					   (u8)mac_value);
		else if (value_length == 2)
			HALMAC_REG_WRITE_16(halmac_adapter, mac_register,
					    (u16)mac_value);
		else if (value_length == 4)
			HALMAC_REG_WRITE_32(halmac_adapter, mac_register,
					    mac_value);

		curr_restore_info++;
	}
}