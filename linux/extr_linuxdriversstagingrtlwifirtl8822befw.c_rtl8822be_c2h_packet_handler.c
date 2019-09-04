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
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  C2H_8822B_BT_INFO 129 
#define  C2H_8822B_BT_MP 128 
 int /*<<< orphan*/  COMP_FW ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  RT_PRINT_DATA (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  rtl8822be_c2h_content_parsing (struct ieee80211_hw*,int,int,int*) ; 
 int /*<<< orphan*/  rtl_c2hcmd_enqueue (struct ieee80211_hw*,int,int,int*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_c2h_packet_handler(struct ieee80211_hw *hw, u8 *buffer, u8 len)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 c2h_cmd_id = 0, c2h_cmd_seq = 0, c2h_cmd_len = 0;
	u8 *tmp_buf = NULL;

	c2h_cmd_id = buffer[0];
	c2h_cmd_seq = buffer[1];
	c2h_cmd_len = len - 2;
	tmp_buf = buffer + 2;

	RT_TRACE(rtlpriv, COMP_FW, DBG_TRACE,
		 "[C2H packet], c2hCmdId=0x%x, c2hCmdSeq=0x%x, c2hCmdLen=%d\n",
		 c2h_cmd_id, c2h_cmd_seq, c2h_cmd_len);

	RT_PRINT_DATA(rtlpriv, COMP_FW, DBG_TRACE,
		      "[C2H packet], Content Hex:\n", tmp_buf, c2h_cmd_len);

	switch (c2h_cmd_id) {
	case C2H_8822B_BT_INFO:
	case C2H_8822B_BT_MP:
		rtl_c2hcmd_enqueue(hw, c2h_cmd_id, c2h_cmd_len, tmp_buf);
		break;
	default:
		rtl8822be_c2h_content_parsing(hw, c2h_cmd_id, c2h_cmd_len,
					      tmp_buf);
		break;
	}
}