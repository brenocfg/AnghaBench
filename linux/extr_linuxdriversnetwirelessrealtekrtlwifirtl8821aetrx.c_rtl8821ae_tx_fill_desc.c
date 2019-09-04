#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct tx_desc_8821ae {int dummy; } ;
struct sk_buff {unsigned int len; scalar_t__ data; } ;
struct rtlwifi_tx_info {int dummy; } ;
struct rtl_tcb_desc {int /*<<< orphan*/  mac_id; scalar_t__ ratr_index; scalar_t__ use_driver_rate; scalar_t__ disable_ratefallback; scalar_t__ tx_enable_sw_calc_duration; scalar_t__ rts_use_shortgi; scalar_t__ rts_use_shortpreamble; int /*<<< orphan*/  rts_rate; int /*<<< orphan*/  rts_sc; scalar_t__ cts_enable; scalar_t__ rts_enable; scalar_t__ use_shortpreamble; scalar_t__ use_shortgi; int /*<<< orphan*/  hw_rate; scalar_t__ empkt_num; } ;
struct rtl_priv {int dummy; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_mac {scalar_t__ rdg_en; } ;
struct rtl_hal {scalar_t__ earlymode_enable; } ;
struct TYPE_4__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct TYPE_3__ {int ampdu_density; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; } ;
struct ieee80211_key_conf {int cipher; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int frame_control; int seq_ctrl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PCI_TX_DESC_CONTENT (int*,int) ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 int /*<<< orphan*/  DESC_RATE54M ; 
 int /*<<< orphan*/  DESC_RATEMCS0 ; 
 scalar_t__ EM_HDR_LEN ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREFRAGS ; 
 int /*<<< orphan*/  IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SET_TX_DESC_AGG_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_AMPDU_DENSITY (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_BMC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_CTS2SELF (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_BW (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_RATE_FB_LIMIT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_SHORTGI (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DISABLE_FB (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HTC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_EN (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_SEL (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_HW_RTS_ENABLE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MAX_AGG_NUM (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_MORE_FRAG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_NAV_USE_HDR (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_OFFSET (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (int*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_DESC_RDG_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_RATE_FB_LIMIT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SC (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SHORT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEC_TYPE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEQ (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_ADDRESS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_SUB_CARRIER (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int*,int) ; 
 scalar_t__ USB_HWDESC_HEADER_LEN ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  _rtl8821ae_insert_emcontent (struct rtl_tcb_desc*,int*) ; 
 int _rtl8821ae_map_hwqueue_to_fwqueue (struct sk_buff*,int) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_ctl (int) ; 
 scalar_t__ ieee80211_is_data_qos (int) ; 
 scalar_t__ ieee80211_is_nullfunc (int) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_bw_mapping (struct ieee80211_hw*,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  rtl8821ae_dm_set_tx_ant_by_tx_info (struct ieee80211_hw*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8821ae_sc_mapping (struct ieee80211_hw*,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  rtl_get_tcb_desc (struct ieee80211_hw*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,struct rtl_tcb_desc*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_set_tx_report (struct rtl_tcb_desc*,int*,struct ieee80211_hw*,struct rtlwifi_tx_info*) ; 
 struct rtlwifi_tx_info* rtl_tx_skb_cb_info (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,scalar_t__) ; 

void rtl8821ae_tx_fill_desc(struct ieee80211_hw *hw,
			    struct ieee80211_hdr *hdr, u8 *pdesc_tx, u8 *txbd,
			    struct ieee80211_tx_info *info,
			    struct ieee80211_sta *sta,
			    struct sk_buff *skb,
			    u8 hw_queue, struct rtl_tcb_desc *ptcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtlwifi_tx_info *tx_info = rtl_tx_skb_cb_info(skb);
	u8 *pdesc = (u8 *)pdesc_tx;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	unsigned int buf_len = 0;
	unsigned int skb_len = skb->len;
	u8 fw_qsel = _rtl8821ae_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			  cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);
	bool lastseg = ((hdr->frame_control &
			 cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);
	dma_addr_t mapping;
	u8 short_gi = 0;

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;
	rtl_get_tcb_desc(hw, info, sta, skb, ptcb_desc);
	/* reserve 8 byte for AMPDU early mode */
	if (rtlhal->earlymode_enable) {
		skb_push(skb, EM_HDR_LEN);
		memset(skb->data, 0, EM_HDR_LEN);
	}
	buf_len = skb->len;
	mapping = pci_map_single(rtlpci->pdev, skb->data, skb->len,
				 PCI_DMA_TODEVICE);
	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	CLEAR_PCI_TX_DESC_CONTENT(pdesc, sizeof(struct tx_desc_8821ae));
	if (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) {
		firstseg = true;
		lastseg = true;
	}
	if (firstseg) {
		if (rtlhal->earlymode_enable) {
			SET_TX_DESC_PKT_OFFSET(pdesc, 1);
			SET_TX_DESC_OFFSET(pdesc, USB_HWDESC_HEADER_LEN +
					   EM_HDR_LEN);
			if (ptcb_desc->empkt_num) {
				RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
					 "Insert 8 byte.pTcb->EMPktNum:%d\n",
					  ptcb_desc->empkt_num);
				_rtl8821ae_insert_emcontent(ptcb_desc,
					 (u8 *)(skb->data));
			}
		} else {
			SET_TX_DESC_OFFSET(pdesc, USB_HWDESC_HEADER_LEN);
		}


		/* ptcb_desc->use_driver_rate = true; */
		SET_TX_DESC_TX_RATE(pdesc, ptcb_desc->hw_rate);
		if (ptcb_desc->hw_rate > DESC_RATEMCS0)
			short_gi = (ptcb_desc->use_shortgi) ? 1 : 0;
		else
			short_gi = (ptcb_desc->use_shortpreamble) ? 1 : 0;

		SET_TX_DESC_DATA_SHORTGI(pdesc, short_gi);

		if (info->flags & IEEE80211_TX_CTL_AMPDU) {
			SET_TX_DESC_AGG_ENABLE(pdesc, 1);
			SET_TX_DESC_MAX_AGG_NUM(pdesc, 0x1f);
		}
		SET_TX_DESC_SEQ(pdesc, seq_number);
		SET_TX_DESC_RTS_ENABLE(pdesc, ((ptcb_desc->rts_enable &&
					!ptcb_desc->cts_enable) ? 1 : 0));
		SET_TX_DESC_HW_RTS_ENABLE(pdesc, 0);
		SET_TX_DESC_CTS2SELF(pdesc, ((ptcb_desc->cts_enable) ? 1 : 0));

		SET_TX_DESC_RTS_RATE(pdesc, ptcb_desc->rts_rate);
		SET_TX_DESC_RTS_SC(pdesc, ptcb_desc->rts_sc);
		SET_TX_DESC_RTS_SHORT(pdesc,
			((ptcb_desc->rts_rate <= DESC_RATE54M) ?
			(ptcb_desc->rts_use_shortpreamble ? 1 : 0) :
			(ptcb_desc->rts_use_shortgi ? 1 : 0)));

		if (ptcb_desc->tx_enable_sw_calc_duration)
			SET_TX_DESC_NAV_USE_HDR(pdesc, 1);

		SET_TX_DESC_DATA_BW(pdesc,
			rtl8821ae_bw_mapping(hw, ptcb_desc));

		SET_TX_DESC_TX_SUB_CARRIER(pdesc,
			rtl8821ae_sc_mapping(hw, ptcb_desc));

		SET_TX_DESC_LINIP(pdesc, 0);
		SET_TX_DESC_PKT_SIZE(pdesc, (u16)skb_len);
		if (sta) {
			u8 ampdu_density = sta->ht_cap.ampdu_density;

			SET_TX_DESC_AMPDU_DENSITY(pdesc, ampdu_density);
		}
		if (info->control.hw_key) {
			struct ieee80211_key_conf *keyconf =
				info->control.hw_key;
			switch (keyconf->cipher) {
			case WLAN_CIPHER_SUITE_WEP40:
			case WLAN_CIPHER_SUITE_WEP104:
			case WLAN_CIPHER_SUITE_TKIP:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x1);
				break;
			case WLAN_CIPHER_SUITE_CCMP:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x3);
				break;
			default:
				SET_TX_DESC_SEC_TYPE(pdesc, 0x0);
				break;
			}
		}

		SET_TX_DESC_QUEUE_SEL(pdesc, fw_qsel);
		SET_TX_DESC_DATA_RATE_FB_LIMIT(pdesc, 0x1F);
		SET_TX_DESC_RTS_RATE_FB_LIMIT(pdesc, 0xF);
		SET_TX_DESC_DISABLE_FB(pdesc, ptcb_desc->disable_ratefallback ?
				       1 : 0);
		SET_TX_DESC_USE_RATE(pdesc, ptcb_desc->use_driver_rate ? 1 : 0);

		if (ieee80211_is_data_qos(fc)) {
			if (mac->rdg_en) {
				RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
					 "Enable RDG function.\n");
				SET_TX_DESC_RDG_ENABLE(pdesc, 1);
				SET_TX_DESC_HTC(pdesc, 1);
			}
		}
		/* tx report */
		rtl_set_tx_report(ptcb_desc, pdesc, hw, tx_info);
	}

	SET_TX_DESC_FIRST_SEG(pdesc, (firstseg ? 1 : 0));
	SET_TX_DESC_LAST_SEG(pdesc, (lastseg ? 1 : 0));
	SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16)buf_len);
	SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);
	/* if (rtlpriv->dm.useramask) { */
	if (1) {
		SET_TX_DESC_RATE_ID(pdesc, ptcb_desc->ratr_index);
		SET_TX_DESC_MACID(pdesc, ptcb_desc->mac_id);
	} else {
		SET_TX_DESC_RATE_ID(pdesc, 0xC + ptcb_desc->ratr_index);
		SET_TX_DESC_MACID(pdesc, ptcb_desc->mac_id);
	}
	if (!ieee80211_is_data_qos(fc))  {
		SET_TX_DESC_HWSEQ_EN(pdesc, 1);
		SET_TX_DESC_HWSEQ_SEL(pdesc, 0);
	}
	SET_TX_DESC_MORE_FRAG(pdesc, (lastseg ? 0 : 1));
	if (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) {
		SET_TX_DESC_BMC(pdesc, 1);
	}

	rtl8821ae_dm_set_tx_ant_by_tx_info(hw, pdesc, ptcb_desc->mac_id);
	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
}