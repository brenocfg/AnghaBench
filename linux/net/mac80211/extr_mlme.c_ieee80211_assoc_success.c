#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct TYPE_21__ {int* mac_cap_info; } ;
struct TYPE_22__ {int has_he; TYPE_5__ he_cap_elem; } ;
struct TYPE_25__ {int rx_nss; int mfp; int wme; int addr; TYPE_6__ he_cap; } ;
struct sta_info {TYPE_9__ sta; } ;
struct ieee802_11_elems {int* ext_capab; int ext_capab_len; int* opmode_notif; TYPE_10__* max_idle_period_ie; int /*<<< orphan*/  mu_edca_param_set; int /*<<< orphan*/  wmm_param_len; scalar_t__ wmm_param; int /*<<< orphan*/  he_spr; TYPE_13__* he_operation; int /*<<< orphan*/ * uora_element; int /*<<< orphan*/  he_cap_len; scalar_t__ he_cap; scalar_t__ vht_cap_elem; scalar_t__ ht_cap_elem; scalar_t__ vht_operation; scalar_t__ ht_operation; int /*<<< orphan*/  supp_rates; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_bss_conf {int he_support; int twt_requester; int multi_sta_back_32bit; int ack_enabled; int uora_exists; int nontransmitted; int protected_keep_alive; int aid; int assoc_capability; void* max_idle_period; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  bssid_indicator; int /*<<< orphan*/  transmitter_bssid; int /*<<< orphan*/  uora_ocw_range; void* frame_time_rts_th; void* htc_trig_based_pkt_ext; void* bss_color; } ;
struct TYPE_15__ {struct ieee80211_bss_conf bss_conf; } ;
struct ieee80211_if_managed {int broken_ap; int aid; int tdls_chan_switch_prohibited; int flags; int wmm_last_param_set; int mu_edca_last_param_set; scalar_t__ use_4addr; struct ieee80211_mgd_assoc_data* assoc_data; } ;
struct TYPE_17__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_11__ vif; TYPE_1__ u; } ;
struct TYPE_18__ {int* variable; int /*<<< orphan*/  capab_info; int /*<<< orphan*/  aid; } ;
struct TYPE_19__ {TYPE_2__ assoc_resp; } ;
struct ieee80211_mgmt {int /*<<< orphan*/  bssid; TYPE_3__ u; } ;
struct ieee80211_mgd_assoc_data {scalar_t__ wmm; TYPE_4__* bss; } ;
struct TYPE_24__ {scalar_t__ queues; } ;
struct ieee80211_local {int /*<<< orphan*/  sta_mtx; TYPE_8__ hw; } ;
struct ieee80211_hdr {int dummy; } ;
struct cfg80211_bss_ies {size_t len; int* data; } ;
struct cfg80211_bss {int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  max_bssid_indicator; TYPE_7__* transmitted_bss; int /*<<< orphan*/  bssid; int /*<<< orphan*/  ies; } ;
struct TYPE_23__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_20__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_16__ {int /*<<< orphan*/  he_oper_params; } ;
struct TYPE_14__ {int idle_options; int /*<<< orphan*/  max_idle_period; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_KEEP_ALIVE ; 
 int /*<<< orphan*/  BSS_CHANGED_QOS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP ; 
 int IEEE80211_HE_MAC_CAP2_ACK_EN ; 
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_BSS_COLOR_MASK ; 
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_DFLT_PE_DURATION_MASK ; 
 int /*<<< orphan*/  IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK ; 
 int IEEE80211_MAX_AID ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_MASK ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT ; 
 int IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF ; 
 int /*<<< orphan*/  IEEE80211_STA_ASSOC ; 
 int /*<<< orphan*/  IEEE80211_STA_AUTHORIZED ; 
 int IEEE80211_STA_CONTROL_PORT ; 
 int IEEE80211_STA_DISABLE_HE ; 
 int IEEE80211_STA_DISABLE_HT ; 
 int IEEE80211_STA_DISABLE_VHT ; 
 int IEEE80211_STA_DISABLE_WMM ; 
 int IEEE80211_STA_MFP_ENABLED ; 
 scalar_t__ WARN_ON (int) ; 
 int WLAN_EXT_CAPA5_TDLS_CH_SW_PROHIBITED ; 
 int WLAN_IDLE_OPTIONS_PROTECTED_KEEP_ALIVE ; 
 int /*<<< orphan*/  WLAN_STA_MFP ; 
 int __sta_info_destroy (struct sta_info*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_he_cap_ie_to_sta_he_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,scalar_t__,int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_he_op_ie_to_bss_conf (TYPE_11__*,TYPE_13__*) ; 
 int /*<<< orphan*/  ieee80211_he_spr_ie_to_bss_conf (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ht_cap_ie_to_sta_ht_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,scalar_t__,struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_recalc_twt_req (struct ieee80211_sub_if_data*,struct sta_info*,struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  ieee80211_send_4addr_nullfunc (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_set_associated (struct ieee80211_sub_if_data*,struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_set_wmm_default (struct ieee80211_sub_if_data*,int,int) ; 
 int /*<<< orphan*/  ieee80211_sta_reset_beacon_monitor (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_sta_rx_notify (struct ieee80211_sub_if_data*,struct ieee80211_hdr*) ; 
 int /*<<< orphan*/  ieee80211_sta_wmm_params (struct ieee80211_local*,struct ieee80211_sub_if_data*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vht_cap_ie_to_sta_vht_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,scalar_t__,struct sta_info*) ; 
 int /*<<< orphan*/  ieee802_11_parse_elems (int*,size_t,int,struct ieee802_11_elems*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cfg80211_bss_ies const*) ; 
 struct cfg80211_bss_ies* kmemdup (struct cfg80211_bss_ies const*,size_t,int /*<<< orphan*/ ) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rate_control_rate_init (struct sta_info*) ; 
 struct cfg80211_bss_ies* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,...) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int sta_info_move_state (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_assoc_success(struct ieee80211_sub_if_data *sdata,
				    struct cfg80211_bss *cbss,
				    struct ieee80211_mgmt *mgmt, size_t len)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_supported_band *sband;
	struct sta_info *sta;
	u8 *pos;
	u16 capab_info, aid;
	struct ieee802_11_elems elems;
	struct ieee80211_bss_conf *bss_conf = &sdata->vif.bss_conf;
	const struct cfg80211_bss_ies *bss_ies = NULL;
	struct ieee80211_mgd_assoc_data *assoc_data = ifmgd->assoc_data;
	u32 changed = 0;
	int err;
	bool ret;

	/* AssocResp and ReassocResp have identical structure */

	aid = le16_to_cpu(mgmt->u.assoc_resp.aid);
	capab_info = le16_to_cpu(mgmt->u.assoc_resp.capab_info);

	/*
	 * The 5 MSB of the AID field are reserved
	 * (802.11-2016 9.4.1.8 AID field)
	 */
	aid &= 0x7ff;

	ifmgd->broken_ap = false;

	if (aid == 0 || aid > IEEE80211_MAX_AID) {
		sdata_info(sdata, "invalid AID value %d (out of range), turn off PS\n",
			   aid);
		aid = 0;
		ifmgd->broken_ap = true;
	}

	pos = mgmt->u.assoc_resp.variable;
	ieee802_11_parse_elems(pos, len - (pos - (u8 *)mgmt), false, &elems,
			       mgmt->bssid, assoc_data->bss->bssid);

	if (!elems.supp_rates) {
		sdata_info(sdata, "no SuppRates element in AssocResp\n");
		return false;
	}

	ifmgd->aid = aid;
	ifmgd->tdls_chan_switch_prohibited =
		elems.ext_capab && elems.ext_capab_len >= 5 &&
		(elems.ext_capab[4] & WLAN_EXT_CAPA5_TDLS_CH_SW_PROHIBITED);

	/*
	 * Some APs are erroneously not including some information in their
	 * (re)association response frames. Try to recover by using the data
	 * from the beacon or probe response. This seems to afflict mobile
	 * 2G/3G/4G wifi routers, reported models include the "Onda PN51T",
	 * "Vodafone PocketWiFi 2", "ZTE MF60" and a similar T-Mobile device.
	 */
	if ((assoc_data->wmm && !elems.wmm_param) ||
	    (!(ifmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	     (!elems.ht_cap_elem || !elems.ht_operation)) ||
	    (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	     (!elems.vht_cap_elem || !elems.vht_operation))) {
		const struct cfg80211_bss_ies *ies;
		struct ieee802_11_elems bss_elems;

		rcu_read_lock();
		ies = rcu_dereference(cbss->ies);
		if (ies)
			bss_ies = kmemdup(ies, sizeof(*ies) + ies->len,
					  GFP_ATOMIC);
		rcu_read_unlock();
		if (!bss_ies)
			return false;

		ieee802_11_parse_elems(bss_ies->data, bss_ies->len,
				       false, &bss_elems,
				       mgmt->bssid,
				       assoc_data->bss->bssid);
		if (assoc_data->wmm &&
		    !elems.wmm_param && bss_elems.wmm_param) {
			elems.wmm_param = bss_elems.wmm_param;
			sdata_info(sdata,
				   "AP bug: WMM param missing from AssocResp\n");
		}

		/*
		 * Also check if we requested HT/VHT, otherwise the AP doesn't
		 * have to include the IEs in the (re)association response.
		 */
		if (!elems.ht_cap_elem && bss_elems.ht_cap_elem &&
		    !(ifmgd->flags & IEEE80211_STA_DISABLE_HT)) {
			elems.ht_cap_elem = bss_elems.ht_cap_elem;
			sdata_info(sdata,
				   "AP bug: HT capability missing from AssocResp\n");
		}
		if (!elems.ht_operation && bss_elems.ht_operation &&
		    !(ifmgd->flags & IEEE80211_STA_DISABLE_HT)) {
			elems.ht_operation = bss_elems.ht_operation;
			sdata_info(sdata,
				   "AP bug: HT operation missing from AssocResp\n");
		}
		if (!elems.vht_cap_elem && bss_elems.vht_cap_elem &&
		    !(ifmgd->flags & IEEE80211_STA_DISABLE_VHT)) {
			elems.vht_cap_elem = bss_elems.vht_cap_elem;
			sdata_info(sdata,
				   "AP bug: VHT capa missing from AssocResp\n");
		}
		if (!elems.vht_operation && bss_elems.vht_operation &&
		    !(ifmgd->flags & IEEE80211_STA_DISABLE_VHT)) {
			elems.vht_operation = bss_elems.vht_operation;
			sdata_info(sdata,
				   "AP bug: VHT operation missing from AssocResp\n");
		}
	}

	/*
	 * We previously checked these in the beacon/probe response, so
	 * they should be present here. This is just a safety net.
	 */
	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HT) &&
	    (!elems.wmm_param || !elems.ht_cap_elem || !elems.ht_operation)) {
		sdata_info(sdata,
			   "HT AP is missing WMM params or HT capability/operation\n");
		ret = false;
		goto out;
	}

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_VHT) &&
	    (!elems.vht_cap_elem || !elems.vht_operation)) {
		sdata_info(sdata,
			   "VHT AP is missing VHT capability/operation\n");
		ret = false;
		goto out;
	}

	mutex_lock(&sdata->local->sta_mtx);
	/*
	 * station info was already allocated and inserted before
	 * the association and should be available to us
	 */
	sta = sta_info_get(sdata, cbss->bssid);
	if (WARN_ON(!sta)) {
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		goto out;
	}

	sband = ieee80211_get_sband(sdata);
	if (!sband) {
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		goto out;
	}

	if (!(ifmgd->flags & IEEE80211_STA_DISABLE_HE) &&
	    (!elems.he_cap || !elems.he_operation)) {
		mutex_unlock(&sdata->local->sta_mtx);
		sdata_info(sdata,
			   "HE AP is missing HE capability/operation\n");
		ret = false;
		goto out;
	}

	/* Set up internal HT/VHT capabilities */
	if (elems.ht_cap_elem && !(ifmgd->flags & IEEE80211_STA_DISABLE_HT))
		ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
						  elems.ht_cap_elem, sta);

	if (elems.vht_cap_elem && !(ifmgd->flags & IEEE80211_STA_DISABLE_VHT))
		ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
						    elems.vht_cap_elem, sta);

	if (elems.he_operation && !(ifmgd->flags & IEEE80211_STA_DISABLE_HE) &&
	    elems.he_cap) {
		ieee80211_he_cap_ie_to_sta_he_cap(sdata, sband,
						  elems.he_cap,
						  elems.he_cap_len,
						  sta);

		bss_conf->he_support = sta->sta.he_cap.has_he;
		changed |= ieee80211_recalc_twt_req(sdata, sta, &elems);
	} else {
		bss_conf->he_support = false;
		bss_conf->twt_requester = false;
	}

	if (bss_conf->he_support) {
		bss_conf->bss_color =
			le32_get_bits(elems.he_operation->he_oper_params,
				      IEEE80211_HE_OPERATION_BSS_COLOR_MASK);

		bss_conf->htc_trig_based_pkt_ext =
			le32_get_bits(elems.he_operation->he_oper_params,
			      IEEE80211_HE_OPERATION_DFLT_PE_DURATION_MASK);
		bss_conf->frame_time_rts_th =
			le32_get_bits(elems.he_operation->he_oper_params,
			      IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK);

		bss_conf->multi_sta_back_32bit =
			sta->sta.he_cap.he_cap_elem.mac_cap_info[2] &
			IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP;

		bss_conf->ack_enabled =
			sta->sta.he_cap.he_cap_elem.mac_cap_info[2] &
			IEEE80211_HE_MAC_CAP2_ACK_EN;

		bss_conf->uora_exists = !!elems.uora_element;
		if (elems.uora_element)
			bss_conf->uora_ocw_range = elems.uora_element[0];

		ieee80211_he_op_ie_to_bss_conf(&sdata->vif, elems.he_operation);
		ieee80211_he_spr_ie_to_bss_conf(&sdata->vif, elems.he_spr);
		/* TODO: OPEN: what happens if BSS color disable is set? */
	}

	if (cbss->transmitted_bss) {
		bss_conf->nontransmitted = true;
		ether_addr_copy(bss_conf->transmitter_bssid,
				cbss->transmitted_bss->bssid);
		bss_conf->bssid_indicator = cbss->max_bssid_indicator;
		bss_conf->bssid_index = cbss->bssid_index;
	}

	/*
	 * Some APs, e.g. Netgear WNDR3700, report invalid HT operation data
	 * in their association response, so ignore that data for our own
	 * configuration. If it changed since the last beacon, we'll get the
	 * next beacon and update then.
	 */

	/*
	 * If an operating mode notification IE is present, override the
	 * NSS calculation (that would be done in rate_control_rate_init())
	 * and use the # of streams from that element.
	 */
	if (elems.opmode_notif &&
	    !(*elems.opmode_notif & IEEE80211_OPMODE_NOTIF_RX_NSS_TYPE_BF)) {
		u8 nss;

		nss = *elems.opmode_notif & IEEE80211_OPMODE_NOTIF_RX_NSS_MASK;
		nss >>= IEEE80211_OPMODE_NOTIF_RX_NSS_SHIFT;
		nss += 1;
		sta->sta.rx_nss = nss;
	}

	rate_control_rate_init(sta);

	if (ifmgd->flags & IEEE80211_STA_MFP_ENABLED) {
		set_sta_flag(sta, WLAN_STA_MFP);
		sta->sta.mfp = true;
	} else {
		sta->sta.mfp = false;
	}

	sta->sta.wme = elems.wmm_param && local->hw.queues >= IEEE80211_NUM_ACS;

	err = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
	if (!err && !(ifmgd->flags & IEEE80211_STA_CONTROL_PORT))
		err = sta_info_move_state(sta, IEEE80211_STA_AUTHORIZED);
	if (err) {
		sdata_info(sdata,
			   "failed to move station %pM to desired state\n",
			   sta->sta.addr);
		WARN_ON(__sta_info_destroy(sta));
		mutex_unlock(&sdata->local->sta_mtx);
		ret = false;
		goto out;
	}

	mutex_unlock(&sdata->local->sta_mtx);

	/*
	 * Always handle WMM once after association regardless
	 * of the first value the AP uses. Setting -1 here has
	 * that effect because the AP values is an unsigned
	 * 4-bit value.
	 */
	ifmgd->wmm_last_param_set = -1;
	ifmgd->mu_edca_last_param_set = -1;

	if (ifmgd->flags & IEEE80211_STA_DISABLE_WMM) {
		ieee80211_set_wmm_default(sdata, false, false);
	} else if (!ieee80211_sta_wmm_params(local, sdata, elems.wmm_param,
					     elems.wmm_param_len,
					     elems.mu_edca_param_set)) {
		/* still enable QoS since we might have HT/VHT */
		ieee80211_set_wmm_default(sdata, false, true);
		/* set the disable-WMM flag in this case to disable
		 * tracking WMM parameter changes in the beacon if
		 * the parameters weren't actually valid. Doing so
		 * avoids changing parameters very strangely when
		 * the AP is going back and forth between valid and
		 * invalid parameters.
		 */
		ifmgd->flags |= IEEE80211_STA_DISABLE_WMM;
	}
	changed |= BSS_CHANGED_QOS;

	if (elems.max_idle_period_ie) {
		bss_conf->max_idle_period =
			le16_to_cpu(elems.max_idle_period_ie->max_idle_period);
		bss_conf->protected_keep_alive =
			!!(elems.max_idle_period_ie->idle_options &
			   WLAN_IDLE_OPTIONS_PROTECTED_KEEP_ALIVE);
		changed |= BSS_CHANGED_KEEP_ALIVE;
	} else {
		bss_conf->max_idle_period = 0;
		bss_conf->protected_keep_alive = false;
	}

	/* set AID and assoc capability,
	 * ieee80211_set_associated() will tell the driver */
	bss_conf->aid = aid;
	bss_conf->assoc_capability = capab_info;
	ieee80211_set_associated(sdata, cbss, changed);

	/*
	 * If we're using 4-addr mode, let the AP know that we're
	 * doing so, so that it can create the STA VLAN on its side
	 */
	if (ifmgd->use_4addr)
		ieee80211_send_4addr_nullfunc(local, sdata);

	/*
	 * Start timer to probe the connection to the AP now.
	 * Also start the timer that will detect beacon loss.
	 */
	ieee80211_sta_rx_notify(sdata, (struct ieee80211_hdr *)mgmt);
	ieee80211_sta_reset_beacon_monitor(sdata);

	ret = true;
 out:
	kfree(bss_ies);
	return ret;
}