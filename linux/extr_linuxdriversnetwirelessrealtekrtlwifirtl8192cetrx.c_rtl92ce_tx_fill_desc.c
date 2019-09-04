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
typedef  int u16 ;
struct tx_desc_92c {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct rtl_tcb_desc {scalar_t__ ratr_index; scalar_t__ mac_id; scalar_t__ use_driver_rate; scalar_t__ packet_bw; scalar_t__ rts_use_shortgi; scalar_t__ rts_use_shortpreamble; int /*<<< orphan*/  rts_rate; int /*<<< orphan*/  rts_sc; scalar_t__ rts_stbc; scalar_t__ cts_enable; scalar_t__ rts_enable; scalar_t__ use_shortpreamble; scalar_t__ use_shortgi; int /*<<< orphan*/  hw_rate; } ;
struct rtl_ps_ctl {scalar_t__ fwctrl_lps; } ;
struct TYPE_6__ {scalar_t__ useramask; } ;
struct rtl_priv {TYPE_3__ dm; } ;
struct rtl_pci {int /*<<< orphan*/  pdev; } ;
struct rtl_mac {scalar_t__ opmode; int bw_40; int cur_40_prime_sc; scalar_t__ rdg_en; int /*<<< orphan*/  bssid; int /*<<< orphan*/  vif; } ;
struct TYPE_5__ {struct ieee80211_key_conf* hw_key; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ control; } ;
struct TYPE_4__ {int ampdu_density; } ;
struct ieee80211_sta {scalar_t__ bandwidth; TYPE_1__ ht_cap; } ;
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
 int /*<<< orphan*/  IEEE80211_FCTL_MOREFRAGS ; 
 int /*<<< orphan*/  IEEE80211_SCTL_FRAG ; 
 int IEEE80211_SCTL_SEQ ; 
 scalar_t__ IEEE80211_STA_RX_BW_40 ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SET_TX_DESC_AGG_BREAK (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_AMPDU_DENSITY (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_BMC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_CTS2SELF (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_BW (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_RATE_FB_LIMIT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DATA_SHORTGI (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_DISABLE_FB (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_FIRST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HTC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HWSEQ_EN (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_HW_RTS_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LAST_SEG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_LINIP (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_MACID (int*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_DESC_MAX_AGG_NUM (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_MORE_FRAG (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_OFFSET (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_ID (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_PKT_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QOS (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_QUEUE_SEL (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RATE_ID (int*,scalar_t__) ; 
 int /*<<< orphan*/  SET_TX_DESC_RDG_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_BW (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_ENABLE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_RATE_FB_LIMIT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SC (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_SHORT (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_RTS_STBC (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEC_TYPE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_SEQ (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_ADDRESS (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_BUFFER_SIZE (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_RATE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_TX_DESC_TX_SUB_CARRIER (int*,int) ; 
 int /*<<< orphan*/  SET_TX_DESC_USE_RATE (int*,int) ; 
 int /*<<< orphan*/  USB_HWDESC_HEADER_LEN ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int _rtl92ce_map_hwqueue_to_fwqueue (struct sk_buff*,int) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* get_sta (struct ieee80211_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_get_DA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_ctl (int) ; 
 scalar_t__ ieee80211_is_data_qos (int) ; 
 scalar_t__ ieee80211_is_nullfunc (int) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int) ; 
 scalar_t__ pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtl_get_tcb_desc (struct ieee80211_hw*,struct ieee80211_tx_info*,struct ieee80211_sta*,struct sk_buff*,struct rtl_tcb_desc*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_pci* rtl_pcidev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_pcipriv (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_ps_ctl* rtl_psc (struct rtl_priv*) ; 

void rtl92ce_tx_fill_desc(struct ieee80211_hw *hw,
			  struct ieee80211_hdr *hdr, u8 *pdesc_tx,
			  u8 *pbd_desc_tx, struct ieee80211_tx_info *info,
			  struct ieee80211_sta *sta,
			  struct sk_buff *skb,
			  u8 hw_queue, struct rtl_tcb_desc *tcb_desc)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_pci *rtlpci = rtl_pcidev(rtl_pcipriv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	bool defaultadapter = true;
	u8 *pdesc = pdesc_tx;
	u16 seq_number;
	__le16 fc = hdr->frame_control;
	u8 fw_qsel = _rtl92ce_map_hwqueue_to_fwqueue(skb, hw_queue);
	bool firstseg = ((hdr->seq_ctrl &
			  cpu_to_le16(IEEE80211_SCTL_FRAG)) == 0);

	bool lastseg = ((hdr->frame_control &
			 cpu_to_le16(IEEE80211_FCTL_MOREFRAGS)) == 0);

	dma_addr_t mapping = pci_map_single(rtlpci->pdev,
					    skb->data, skb->len,
					    PCI_DMA_TODEVICE);

	u8 bw_40 = 0;

	if (pci_dma_mapping_error(rtlpci->pdev, mapping)) {
		RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
			 "DMA mapping error\n");
		return;
	}
	rcu_read_lock();
	sta = get_sta(hw, mac->vif, mac->bssid);
	if (mac->opmode == NL80211_IFTYPE_STATION) {
		bw_40 = mac->bw_40;
	} else if (mac->opmode == NL80211_IFTYPE_AP ||
		   mac->opmode == NL80211_IFTYPE_ADHOC ||
		   mac->opmode == NL80211_IFTYPE_MESH_POINT) {
		if (sta)
			bw_40 = sta->bandwidth >= IEEE80211_STA_RX_BW_40;
	}

	seq_number = (le16_to_cpu(hdr->seq_ctrl) & IEEE80211_SCTL_SEQ) >> 4;

	rtl_get_tcb_desc(hw, info, sta, skb, tcb_desc);

	CLEAR_PCI_TX_DESC_CONTENT(pdesc, sizeof(struct tx_desc_92c));

	if (ieee80211_is_nullfunc(fc) || ieee80211_is_ctl(fc)) {
		firstseg = true;
		lastseg = true;
	}
	if (firstseg) {
		SET_TX_DESC_OFFSET(pdesc, USB_HWDESC_HEADER_LEN);

		SET_TX_DESC_TX_RATE(pdesc, tcb_desc->hw_rate);

		if (tcb_desc->use_shortgi || tcb_desc->use_shortpreamble)
			SET_TX_DESC_DATA_SHORTGI(pdesc, 1);

		if (info->flags & IEEE80211_TX_CTL_AMPDU) {
			SET_TX_DESC_AGG_BREAK(pdesc, 1);
			SET_TX_DESC_MAX_AGG_NUM(pdesc, 0x14);
		}
		SET_TX_DESC_SEQ(pdesc, seq_number);

		SET_TX_DESC_RTS_ENABLE(pdesc, ((tcb_desc->rts_enable &&
						!tcb_desc->
						cts_enable) ? 1 : 0));
		SET_TX_DESC_HW_RTS_ENABLE(pdesc,
					  ((tcb_desc->rts_enable
					    || tcb_desc->cts_enable) ? 1 : 0));
		SET_TX_DESC_CTS2SELF(pdesc, ((tcb_desc->cts_enable) ? 1 : 0));
		SET_TX_DESC_RTS_STBC(pdesc, ((tcb_desc->rts_stbc) ? 1 : 0));

		SET_TX_DESC_RTS_RATE(pdesc, tcb_desc->rts_rate);
		SET_TX_DESC_RTS_BW(pdesc, 0);
		SET_TX_DESC_RTS_SC(pdesc, tcb_desc->rts_sc);
		SET_TX_DESC_RTS_SHORT(pdesc,
				      ((tcb_desc->rts_rate <= DESC_RATE54M) ?
				       (tcb_desc->rts_use_shortpreamble ? 1 : 0)
				       : (tcb_desc->rts_use_shortgi ? 1 : 0)));

		if (bw_40) {
			if (tcb_desc->packet_bw) {
				SET_TX_DESC_DATA_BW(pdesc, 1);
				SET_TX_DESC_TX_SUB_CARRIER(pdesc, 3);
			} else {
				SET_TX_DESC_DATA_BW(pdesc, 0);
				SET_TX_DESC_TX_SUB_CARRIER(pdesc,
						 mac->cur_40_prime_sc);
			}
		} else {
			SET_TX_DESC_DATA_BW(pdesc, 0);
			SET_TX_DESC_TX_SUB_CARRIER(pdesc, 0);
		}

		SET_TX_DESC_LINIP(pdesc, 0);
		SET_TX_DESC_PKT_SIZE(pdesc, (u16) skb->len);

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

		SET_TX_DESC_PKT_ID(pdesc, 0);
		SET_TX_DESC_QUEUE_SEL(pdesc, fw_qsel);

		SET_TX_DESC_DATA_RATE_FB_LIMIT(pdesc, 0x1F);
		SET_TX_DESC_RTS_RATE_FB_LIMIT(pdesc, 0xF);
		SET_TX_DESC_DISABLE_FB(pdesc, 0);
		SET_TX_DESC_USE_RATE(pdesc, tcb_desc->use_driver_rate ? 1 : 0);

		if (ieee80211_is_data_qos(fc)) {
			if (mac->rdg_en) {
				RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE,
					 "Enable RDG function\n");
				SET_TX_DESC_RDG_ENABLE(pdesc, 1);
				SET_TX_DESC_HTC(pdesc, 1);
			}
		}
	}
	rcu_read_unlock();

	SET_TX_DESC_FIRST_SEG(pdesc, (firstseg ? 1 : 0));
	SET_TX_DESC_LAST_SEG(pdesc, (lastseg ? 1 : 0));

	SET_TX_DESC_TX_BUFFER_SIZE(pdesc, (u16) skb->len);

	SET_TX_DESC_TX_BUFFER_ADDRESS(pdesc, mapping);

	if (rtlpriv->dm.useramask) {
		SET_TX_DESC_RATE_ID(pdesc, tcb_desc->ratr_index);
		SET_TX_DESC_MACID(pdesc, tcb_desc->mac_id);
	} else {
		SET_TX_DESC_RATE_ID(pdesc, 0xC + tcb_desc->ratr_index);
		SET_TX_DESC_MACID(pdesc, tcb_desc->ratr_index);
	}

	if ((!ieee80211_is_data_qos(fc)) && ppsc->fwctrl_lps) {
		SET_TX_DESC_HWSEQ_EN(pdesc, 1);
		SET_TX_DESC_PKT_ID(pdesc, 8);

		if (!defaultadapter)
			SET_TX_DESC_QOS(pdesc, 1);
	}

	SET_TX_DESC_MORE_FRAG(pdesc, (lastseg ? 0 : 1));

	if (is_multicast_ether_addr(ieee80211_get_DA(hdr)) ||
	    is_broadcast_ether_addr(ieee80211_get_DA(hdr))) {
		SET_TX_DESC_BMC(pdesc, 1);
	}

	RT_TRACE(rtlpriv, COMP_SEND, DBG_TRACE, "\n");
}