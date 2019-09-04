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
typedef  int u64 ;
typedef  int u32 ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_pci {TYPE_4__* rx_ring; TYPE_3__* tx_ring; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_8__ {scalar_t__ dma; } ;
struct TYPE_7__ {scalar_t__ buffer_desc_dma; } ;
struct TYPE_6__ {TYPE_1__* mod_params; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma64; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 size_t BE_QUEUE ; 
 int BIT (int) ; 
 size_t BK_QUEUE ; 
 int DMA_BIT_MASK (int) ; 
 size_t H2C_QUEUE ; 
 size_t HIGH_QUEUE ; 
 size_t MGNT_QUEUE ; 
 scalar_t__ REG_BCNQ_TXBD_DESA_8822B ; 
 scalar_t__ REG_BD_RWPTR_CLR_8822B ; 
 scalar_t__ REG_BEQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_BEQ_TXBD_NUM_8822B ; 
 scalar_t__ REG_BKQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_BKQ_TXBD_NUM_8822B ; 
 scalar_t__ REG_H2CQ_CSR_8822B ; 
 scalar_t__ REG_H2CQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_H2CQ_TXBD_NUM_8822B ; 
 scalar_t__ REG_HI0Q_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_HI0Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI1Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI2Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI3Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI4Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI5Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI6Q_TXBD_NUM_8822B ; 
 int /*<<< orphan*/  REG_HI7Q_TXBD_NUM_8822B ; 
 scalar_t__ REG_INT_MIG_8822B ; 
 scalar_t__ REG_MCUTST_I_8822B ; 
 scalar_t__ REG_MGQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_MGQ_TXBD_NUM_8822B ; 
 scalar_t__ REG_PCIE_CTRL_8822B ; 
 scalar_t__ REG_RXQ_RXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_RX_RXBD_NUM_8822B ; 
 scalar_t__ REG_VIQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_VIQ_TXBD_NUM_8822B ; 
 scalar_t__ REG_VOQ_TXBD_DESA_8822B ; 
 int /*<<< orphan*/  REG_VOQ_TXBD_NUM_8822B ; 
 int RTL8822BE_SEG_NUM ; 
 int RX_DESC_NUM_8822BE ; 
 size_t RX_MPDU_QUEUE ; 
 int TX_DESC_NUM_8822B ; 
 size_t VI_QUEUE ; 
 size_t VO_QUEUE ; 
 int /*<<< orphan*/  _rtl8822be_gen_refresh_led_state (struct ieee80211_hw*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int rtl_read_dword (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_dword (struct rtl_priv*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool _rtl8822be_init_trxbd(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	/*struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));*/

	u8 bytetmp;
	/*u16 wordtmp;*/
	u32 dwordtmp;

	/* Set TX/RX descriptor physical address -- HI part */
	if (!rtlpriv->cfg->mod_params->dma64)
		goto dma64_end;

	rtl_write_dword(rtlpriv, REG_H2CQ_TXBD_DESA_8822B + 4,
			((u64)rtlpci->tx_ring[H2C_QUEUE].buffer_desc_dma) >>
				32);
	rtl_write_dword(rtlpriv, REG_BCNQ_TXBD_DESA_8822B + 4,
			((u64)rtlpci->tx_ring[BEACON_QUEUE].buffer_desc_dma) >>
				32);
	rtl_write_dword(rtlpriv, REG_MGQ_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[MGNT_QUEUE].buffer_desc_dma >> 32);
	rtl_write_dword(rtlpriv, REG_VOQ_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[VO_QUEUE].buffer_desc_dma >> 32);
	rtl_write_dword(rtlpriv, REG_VIQ_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[VI_QUEUE].buffer_desc_dma >> 32);
	rtl_write_dword(rtlpriv, REG_BEQ_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[BE_QUEUE].buffer_desc_dma >> 32);
	rtl_write_dword(rtlpriv, REG_BKQ_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[BK_QUEUE].buffer_desc_dma >> 32);
	rtl_write_dword(rtlpriv, REG_HI0Q_TXBD_DESA_8822B + 4,
			(u64)rtlpci->tx_ring[HIGH_QUEUE].buffer_desc_dma >> 32);

	rtl_write_dword(rtlpriv, REG_RXQ_RXBD_DESA_8822B + 4,
			(u64)rtlpci->rx_ring[RX_MPDU_QUEUE].dma >> 32);

dma64_end:
	/* Set TX/RX descriptor physical address(from OS API). */
	rtl_write_dword(rtlpriv, REG_H2CQ_TXBD_DESA_8822B,
			((u64)rtlpci->tx_ring[H2C_QUEUE].buffer_desc_dma) &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_BCNQ_TXBD_DESA_8822B,
			((u64)rtlpci->tx_ring[BEACON_QUEUE].buffer_desc_dma) &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_MGQ_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[MGNT_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_VOQ_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[VO_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_VIQ_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[VI_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_BEQ_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[BE_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));
	dwordtmp = rtl_read_dword(rtlpriv, REG_BEQ_TXBD_DESA_8822B); /* need? */
	rtl_write_dword(rtlpriv, REG_BKQ_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[BK_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));
	rtl_write_dword(rtlpriv, REG_HI0Q_TXBD_DESA_8822B,
			(u64)rtlpci->tx_ring[HIGH_QUEUE].buffer_desc_dma &
				DMA_BIT_MASK(32));

	rtl_write_dword(rtlpriv, REG_RXQ_RXBD_DESA_8822B,
			(u64)rtlpci->rx_ring[RX_MPDU_QUEUE].dma &
				DMA_BIT_MASK(32));

	/* Reset R/W point */
	rtl_write_dword(rtlpriv, REG_BD_RWPTR_CLR_8822B, 0x3fffffff);

	/* Reset the H2CQ R/W point index to 0 */
	dwordtmp = rtl_read_dword(rtlpriv, REG_H2CQ_CSR_8822B);
	rtl_write_dword(rtlpriv, REG_H2CQ_CSR_8822B,
			(dwordtmp | BIT(8) | BIT(16)));

	bytetmp = rtl_read_byte(rtlpriv, REG_PCIE_CTRL_8822B + 3);
	rtl_write_byte(rtlpriv, REG_PCIE_CTRL_8822B + 3, bytetmp | 0xF7);

	rtl_write_dword(rtlpriv, REG_INT_MIG_8822B, 0);

	rtl_write_dword(rtlpriv, REG_MCUTST_I_8822B, 0x0);

	rtl_write_word(rtlpriv, REG_H2CQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_MGQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_VOQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_VIQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_BEQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_VOQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_BKQ_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI0Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI1Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI2Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI3Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI4Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI5Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI6Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	rtl_write_word(rtlpriv, REG_HI7Q_TXBD_NUM_8822B,
		       TX_DESC_NUM_8822B |
			       ((RTL8822BE_SEG_NUM << 12) & 0x3000));
	/*Rx*/
	rtl_write_word(rtlpriv, REG_RX_RXBD_NUM_8822B,
		       RX_DESC_NUM_8822BE |
		       ((RTL8822BE_SEG_NUM << 13) & 0x6000) | 0x8000);

	rtl_write_dword(rtlpriv, REG_BD_RWPTR_CLR_8822B, 0XFFFFFFFF);

	_rtl8822be_gen_refresh_led_state(hw);

	return true;
}