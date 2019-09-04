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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ bt_supported_version; } ;
struct btc_coexist {TYPE_1__ bt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OP_GET_BT_COEX_SUPPORTED_VERSION ; 
 int /*<<< orphan*/  halbtc_send_bt_mp_operation (struct btc_coexist*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static u32 halbtc_get_bt_coex_supported_version(void *btc_context)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	u8 cmd_buffer[4] = {0};

	if (btcoexist->bt_info.bt_supported_version)
		goto label_done;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	halbtc_send_bt_mp_operation(btcoexist,
				    BT_OP_GET_BT_COEX_SUPPORTED_VERSION,
				    cmd_buffer, 4, 200);

label_done:
	return btcoexist->bt_info.bt_supported_version;
}