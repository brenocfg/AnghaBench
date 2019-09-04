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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  afh_map_h; int /*<<< orphan*/  afh_map_m; int /*<<< orphan*/  afh_map_l; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OP_GET_AFH_MAP_H ; 
 int /*<<< orphan*/  BT_OP_GET_AFH_MAP_L ; 
 int /*<<< orphan*/  BT_OP_GET_AFH_MAP_M ; 
 int halbtc_send_bt_mp_operation (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static bool halbtc_get_bt_afh_map_from_bt(void *btc_context, u8 map_type,
					  u8 *afh_map)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	u8 cmd_buffer[2] = {0};
	bool ret;
	u32 *afh_map_l = (u32 *)afh_map;
	u32 *afh_map_m = (u32 *)(afh_map + 4);
	u16 *afh_map_h = (u16 *)(afh_map + 8);

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_L,
					  cmd_buffer, 2, 200);
	if (!ret)
		goto exit;

	*afh_map_l = btcoexist->bt_info.afh_map_l;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_M,
					  cmd_buffer, 2, 200);
	if (!ret)
		goto exit;

	*afh_map_m = btcoexist->bt_info.afh_map_m;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	ret = halbtc_send_bt_mp_operation(btcoexist, BT_OP_GET_AFH_MAP_H,
					  cmd_buffer, 2, 200);
	if (!ret)
		goto exit;

	*afh_map_h = btcoexist->bt_info.afh_map_h;

exit:
	return ret;
}