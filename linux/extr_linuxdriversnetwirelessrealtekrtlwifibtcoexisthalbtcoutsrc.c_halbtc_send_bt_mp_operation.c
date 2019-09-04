#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;
struct rtl_priv {TYPE_3__ mac80211; TYPE_2__* cfg; } ;
struct btc_coexist {int /*<<< orphan*/  bt_mp_comp; struct rtl_priv* adapter; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fill_h2c_cmd ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
#define  BT_OP_GET_AFH_MAP_H 141 
#define  BT_OP_GET_AFH_MAP_L 140 
#define  BT_OP_GET_AFH_MAP_M 139 
#define  BT_OP_GET_BT_ANT_DET_VAL 138 
#define  BT_OP_GET_BT_BLE_SCAN_PARA 137 
#define  BT_OP_GET_BT_BLE_SCAN_TYPE 136 
#define  BT_OP_GET_BT_COEX_SUPPORTED_FEATURE 135 
#define  BT_OP_GET_BT_COEX_SUPPORTED_VERSION 134 
#define  BT_OP_GET_BT_DEVICE_INFO 133 
#define  BT_OP_GET_BT_FORBIDDEN_SLOT_VAL 132 
#define  BT_OP_GET_BT_VERSION 131 
#define  BT_OP_READ_REG 130 
#define  BT_OP_WRITE_REG_ADDR 129 
#define  BT_OP_WRITE_REG_VALUE 128 
 int BT_SEQ_DONT_CARE ; 
 int BT_SEQ_GET_AFH_MAP_H ; 
 int BT_SEQ_GET_AFH_MAP_L ; 
 int BT_SEQ_GET_AFH_MAP_M ; 
 int BT_SEQ_GET_BT_ANT_DET_VAL ; 
 int BT_SEQ_GET_BT_BLE_SCAN_PARA ; 
 int BT_SEQ_GET_BT_BLE_SCAN_TYPE ; 
 int BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE ; 
 int BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION ; 
 int BT_SEQ_GET_BT_DEVICE_INFO ; 
 int BT_SEQ_GET_BT_FORB_SLOT_VAL ; 
 int BT_SEQ_GET_BT_VERSION ; 
 int /*<<< orphan*/  COMP_BT_COEXIST ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  halbtc_is_hw_mailbox_exist (struct btc_coexist*) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool halbtc_send_bt_mp_operation(struct btc_coexist *btcoexist, u8 op_code,
				 u8 *cmd, u32 len, unsigned long wait_ms)
{
	struct rtl_priv *rtlpriv;
	const u8 oper_ver = 0;
	u8 req_num;

	if (!halbtc_is_hw_mailbox_exist(btcoexist))
		return false;

	if (wait_ms)	/* before h2c to avoid race condition */
		reinit_completion(&btcoexist->bt_mp_comp);

	rtlpriv = btcoexist->adapter;

	/* fill req_num by op_code, and rtl_btc_btmpinfo_notify() use it
	 * to know message type
	 */
	switch (op_code) {
	case BT_OP_GET_BT_VERSION:
		req_num = BT_SEQ_GET_BT_VERSION;
		break;
	case BT_OP_GET_AFH_MAP_L:
		req_num = BT_SEQ_GET_AFH_MAP_L;
		break;
	case BT_OP_GET_AFH_MAP_M:
		req_num = BT_SEQ_GET_AFH_MAP_M;
		break;
	case BT_OP_GET_AFH_MAP_H:
		req_num = BT_SEQ_GET_AFH_MAP_H;
		break;
	case BT_OP_GET_BT_COEX_SUPPORTED_FEATURE:
		req_num = BT_SEQ_GET_BT_COEX_SUPPORTED_FEATURE;
		break;
	case BT_OP_GET_BT_COEX_SUPPORTED_VERSION:
		req_num = BT_SEQ_GET_BT_COEX_SUPPORTED_VERSION;
		break;
	case BT_OP_GET_BT_ANT_DET_VAL:
		req_num = BT_SEQ_GET_BT_ANT_DET_VAL;
		break;
	case BT_OP_GET_BT_BLE_SCAN_PARA:
		req_num = BT_SEQ_GET_BT_BLE_SCAN_PARA;
		break;
	case BT_OP_GET_BT_BLE_SCAN_TYPE:
		req_num = BT_SEQ_GET_BT_BLE_SCAN_TYPE;
		break;
	case BT_OP_GET_BT_DEVICE_INFO:
		req_num = BT_SEQ_GET_BT_DEVICE_INFO;
		break;
	case BT_OP_GET_BT_FORBIDDEN_SLOT_VAL:
		req_num = BT_SEQ_GET_BT_FORB_SLOT_VAL;
		break;
	case BT_OP_WRITE_REG_ADDR:
	case BT_OP_WRITE_REG_VALUE:
	case BT_OP_READ_REG:
	default:
		req_num = BT_SEQ_DONT_CARE;
		break;
	}

	cmd[0] |= (oper_ver & 0x0f);		/* Set OperVer */
	cmd[0] |= ((req_num << 4) & 0xf0);	/* Set ReqNum */
	cmd[1] = op_code;
	rtlpriv->cfg->ops->fill_h2c_cmd(rtlpriv->mac80211.hw, 0x67, len, cmd);

	/* wait? */
	if (!wait_ms)
		return true;

	RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_LOUD,
		 "btmpinfo wait req_num=%d wait=%ld\n", req_num, wait_ms);

	if (in_interrupt())
		return false;

	if (wait_for_completion_timeout(&btcoexist->bt_mp_comp,
					msecs_to_jiffies(wait_ms)) == 0) {
		RT_TRACE(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
			 "btmpinfo wait (req_num=%d) timeout\n", req_num);

		return false;	/* timeout */
	}

	return true;
}