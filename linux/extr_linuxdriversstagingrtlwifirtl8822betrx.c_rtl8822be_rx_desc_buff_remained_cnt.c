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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {TYPE_1__* rx_ring; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ next_rx_rp; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RXQ_RXBD_IDX_8822B ; 
 scalar_t__ RX_DESC_NUM_8822BE ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

u16 rtl8822be_rx_desc_buff_remained_cnt(struct ieee80211_hw *hw, u8 queue_index)
{
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u16 desc_idx_hw = 0, desc_idx_host = 0, remind_cnt = 0;
	u32 tmp_4byte = 0;

	u32 rw_mask = 0x1ff;

	tmp_4byte = rtl_read_dword(rtlpriv, REG_RXQ_RXBD_IDX_8822B);
	desc_idx_hw = (u16)((tmp_4byte >> 16) & rw_mask);
	desc_idx_host = (u16)(tmp_4byte & rw_mask);

	/* may be no data, donot rx */
	if (desc_idx_hw == desc_idx_host)
		return 0;

	remind_cnt =
		(desc_idx_hw > desc_idx_host) ?
			(desc_idx_hw - desc_idx_host) :
			(RX_DESC_NUM_8822BE - (desc_idx_host - desc_idx_hw));

	rtlpci->rx_ring[queue_index].next_rx_rp = desc_idx_host;

	return remind_cnt;
}