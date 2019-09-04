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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct rtl_priv {int dummy; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RECV ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 scalar_t__ GET_RX_BUFFER_DESC_FS (scalar_t__*) ; 
 scalar_t__ GET_RX_BUFFER_DESC_LS (scalar_t__*) ; 
 scalar_t__ GET_RX_BUFFER_DESC_TOTAL_LENGTH (scalar_t__*) ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8822be_rx_check_dma_ok(struct ieee80211_hw *hw, u8 *header_desc,
			       u8 queue_index)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 first_seg;
	u8 last_seg;
	u16 total_len;
	u16 read_cnt = 0;

	if (!header_desc)
		return;

	do {
		total_len = (u16)GET_RX_BUFFER_DESC_TOTAL_LENGTH(header_desc);
		first_seg = (u8)GET_RX_BUFFER_DESC_FS(header_desc);
		last_seg = (u8)GET_RX_BUFFER_DESC_LS(header_desc);

		if (read_cnt++ > 20) {
			RT_TRACE(rtlpriv, COMP_RECV, DBG_DMESG,
				 "RX chk DMA over %d times\n", read_cnt);
			break;
		}

	} while (total_len == 0 && first_seg == 0 && last_seg == 0);
}