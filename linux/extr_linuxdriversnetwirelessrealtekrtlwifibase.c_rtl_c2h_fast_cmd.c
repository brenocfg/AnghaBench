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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
#define  C2H_BT_MP 128 
 int GET_C2H_CMD_ID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool rtl_c2h_fast_cmd(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	u8 cmd_id = GET_C2H_CMD_ID(skb->data);

	switch (cmd_id) {
	case C2H_BT_MP:
		return true;
	default:
		break;
	}

	return false;
}