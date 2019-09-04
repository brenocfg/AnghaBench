#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_8__ {TYPE_3__* btc_ops; } ;
struct rtl_priv {TYPE_4__ btcoexist; TYPE_2__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct c2h_evt_hdr {int cmd_id; int cmd_len; int cmd_seq; } ;
typedef  int /*<<< orphan*/  c2h_event ;
struct TYPE_7__ {int /*<<< orphan*/  (* btc_periodical ) (struct rtl_priv*) ;} ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_btc_status ) () ;} ;

/* Variables and functions */
 int C2H_EVT_FW_CLOSE ; 
 int C2H_EVT_HOST_CLOSE ; 
#define  C2H_V0_BT_INFO 130 
#define  C2H_V0_BT_OP_MODE 129 
#define  C2H_V0_BT_RSSI 128 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int REG_C2HEVT_MSG_NORMAL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct c2h_evt_hdr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8723e_dm_bt_parse_bt_info (struct ieee80211_hw*,int*,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 void* rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*) ; 

void rtl_8723e_c2h_command_handle(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct c2h_evt_hdr c2h_event;
	u8 *ptmp_buf = NULL;
	u8 index = 0;
	u8 u1b_tmp = 0;
	memset(&c2h_event, 0, sizeof(c2h_event));
	u1b_tmp = rtl_read_byte(rtlpriv, REG_C2HEVT_MSG_NORMAL);
	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
		"&&&&&&: REG_C2HEVT_MSG_NORMAL is 0x%x\n", u1b_tmp);
	c2h_event.cmd_id = u1b_tmp & 0xF;
	c2h_event.cmd_len = (u1b_tmp & 0xF0) >> 4;
	c2h_event.cmd_seq = rtl_read_byte(rtlpriv, REG_C2HEVT_MSG_NORMAL + 1);
	RT_TRACE(rtlpriv, COMP_FW, DBG_DMESG,
		 "cmd_id: %d, cmd_len: %d, cmd_seq: %d\n",
		 c2h_event.cmd_id , c2h_event.cmd_len, c2h_event.cmd_seq);
	u1b_tmp = rtl_read_byte(rtlpriv, 0x01AF);
	if (u1b_tmp == C2H_EVT_HOST_CLOSE) {
		return;
	} else if (u1b_tmp != C2H_EVT_FW_CLOSE) {
		rtl_write_byte(rtlpriv, 0x1AF, 0x00);
		return;
	}
	ptmp_buf = kzalloc(c2h_event.cmd_len, GFP_KERNEL);
	if (ptmp_buf == NULL) {
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			 "malloc cmd buf failed\n");
		return;
	}

	/* Read the content */
	for (index = 0; index < c2h_event.cmd_len; index++)
		ptmp_buf[index] = rtl_read_byte(rtlpriv,
					REG_C2HEVT_MSG_NORMAL + 2 + index);


	switch (c2h_event.cmd_id) {
	case C2H_V0_BT_RSSI:
			break;

	case C2H_V0_BT_OP_MODE:
			break;

	case C2H_V0_BT_INFO:
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[0] (ID) is 0x%x\n",
			c2h_event.cmd_id);
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[1] (Seq) is 0x%x\n",
			c2h_event.cmd_seq);
		RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
			"BT info Byte[2] (Data)= 0x%x\n", ptmp_buf[0]);

		rtl8723e_dm_bt_parse_bt_info(hw, ptmp_buf, c2h_event.cmd_len);

		if (rtlpriv->cfg->ops->get_btc_status())
			rtlpriv->btcoexist.btc_ops->btc_periodical(rtlpriv);

		break;
	default:
		break;
	}
	kfree(ptmp_buf);

	rtl_write_byte(rtlpriv, 0x01AF, C2H_EVT_HOST_CLOSE);
}