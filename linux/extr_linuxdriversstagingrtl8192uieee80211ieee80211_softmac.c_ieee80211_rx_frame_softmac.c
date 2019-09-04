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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct rtl_80211_hdr_3addr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_ctl; } ;
struct ieee80211_rx_stats {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdHTInfoLen; int /*<<< orphan*/  bdHTInfoBuf; int /*<<< orphan*/  bdHTCapLen; int /*<<< orphan*/  bdHTCapBuf; } ;
struct ieee80211_network {TYPE_2__ bssht; } ;
struct TYPE_6__ {int /*<<< orphan*/  reassoc; int /*<<< orphan*/  rx_ass_err; int /*<<< orphan*/  rx_ass_ok; } ;
struct ieee80211_device {scalar_t__ ps; scalar_t__ iw_mode; scalar_t__ state; int softmac_features; int assoc_id; int /*<<< orphan*/  associate_procedure_wq; TYPE_3__ softmac_stats; int /*<<< orphan*/  AsocRetryCount; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* handle_assoc_response ) (int /*<<< orphan*/ ,struct ieee80211_assoc_response_frame*,struct ieee80211_network*) ;TYPE_1__* pHTInfo; int /*<<< orphan*/  qos_support; int /*<<< orphan*/  last_rx_ps_time; int /*<<< orphan*/  ps_task; scalar_t__ sta_sleep; int /*<<< orphan*/  proto_started; } ;
struct ieee80211_assoc_response_frame {int /*<<< orphan*/  info_element; } ;
struct TYPE_4__ {int /*<<< orphan*/  PeerHTInfoBuf; int /*<<< orphan*/  PeerHTCapBuf; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_ASSOCIATING ; 
 scalar_t__ IEEE80211_ASSOCIATING_AUTHENTICATED ; 
 scalar_t__ IEEE80211_ASSOCIATING_AUTHENTICATING ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*,...) ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IEEE80211_PS_DISABLED ; 
#define  IEEE80211_STYPE_ASSOC_REQ 136 
#define  IEEE80211_STYPE_ASSOC_RESP 135 
#define  IEEE80211_STYPE_AUTH 134 
 int IEEE80211_STYPE_BEACON ; 
#define  IEEE80211_STYPE_DEAUTH 133 
#define  IEEE80211_STYPE_DISASSOC 132 
#define  IEEE80211_STYPE_MANAGE_ACT 131 
#define  IEEE80211_STYPE_PROBE_REQ 130 
 int IEEE80211_STYPE_PROBE_RESP ; 
#define  IEEE80211_STYPE_REASSOC_REQ 129 
#define  IEEE80211_STYPE_REASSOC_RESP 128 
 int IEEE_SOFTMAC_ASSOCIATE ; 
 int IEEE_SOFTMAC_PROBERS ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 scalar_t__ IW_MODE_MASTER ; 
 int /*<<< orphan*/  RT_ASOC_RETRY_LIMIT ; 
 int /*<<< orphan*/  RemovePeerTS (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 int WLAN_FC_GET_STYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assoc_parse (struct ieee80211_device*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  ieee80211_associate_abort (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_associate_complete (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_check_auth_response (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_parse_info_param (struct ieee80211_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_network*,struct ieee80211_rx_stats*) ; 
 int /*<<< orphan*/  ieee80211_process_action (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_assoc_rq (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_auth_rq (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx_probe_rq (struct ieee80211_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_network*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_wx_assoc_event (struct ieee80211_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_assoc_response_frame*,struct ieee80211_network*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

inline int
ieee80211_rx_frame_softmac(struct ieee80211_device *ieee, struct sk_buff *skb,
			   struct ieee80211_rx_stats *rx_stats, u16 type,
			   u16 stype)
{
	struct rtl_80211_hdr_3addr *header = (struct rtl_80211_hdr_3addr *)skb->data;
	u16 errcode;
	int aid;
	struct ieee80211_assoc_response_frame *assoc_resp;
//	struct ieee80211_info_element *info_element;

	if (!ieee->proto_started)
		return 0;

	if (ieee->sta_sleep || (ieee->ps != IEEE80211_PS_DISABLED &&
				ieee->iw_mode == IW_MODE_INFRA &&
				ieee->state == IEEE80211_LINKED))
		tasklet_schedule(&ieee->ps_task);

	if (WLAN_FC_GET_STYPE(header->frame_ctl) != IEEE80211_STYPE_PROBE_RESP &&
	    WLAN_FC_GET_STYPE(header->frame_ctl) != IEEE80211_STYPE_BEACON)
		ieee->last_rx_ps_time = jiffies;

	switch (WLAN_FC_GET_STYPE(header->frame_ctl)) {
	case IEEE80211_STYPE_ASSOC_RESP:
	case IEEE80211_STYPE_REASSOC_RESP:
		IEEE80211_DEBUG_MGMT("received [RE]ASSOCIATION RESPONSE (%d)\n",
				WLAN_FC_GET_STYPE(header->frame_ctl));
		if ((ieee->softmac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATED &&
		    ieee->iw_mode == IW_MODE_INFRA) {
			struct ieee80211_network network_resp;
			struct ieee80211_network *network = &network_resp;

			errcode = assoc_parse(ieee, skb, &aid);
			if (!errcode) {
				ieee->state = IEEE80211_LINKED;
				ieee->assoc_id = aid;
				ieee->softmac_stats.rx_ass_ok++;
				/* station support qos */
				/* Let the register setting defaultly with Legacy station */
				if (ieee->qos_support) {
					assoc_resp = (struct ieee80211_assoc_response_frame *)skb->data;
					memset(network, 0, sizeof(*network));
					if (ieee80211_parse_info_param(ieee, assoc_resp->info_element,\
								       rx_stats->len - sizeof(*assoc_resp), \
								       network, rx_stats)) {
						return 1;
					} else {
						//filling the PeerHTCap. //maybe not necessary as we can get its info from current_network.
						memcpy(ieee->pHTInfo->PeerHTCapBuf, network->bssht.bdHTCapBuf, network->bssht.bdHTCapLen);
						memcpy(ieee->pHTInfo->PeerHTInfoBuf, network->bssht.bdHTInfoBuf, network->bssht.bdHTInfoLen);
					}
					if (ieee->handle_assoc_response != NULL)
						ieee->handle_assoc_response(ieee->dev, (struct ieee80211_assoc_response_frame *)header, network);
				}
				ieee80211_associate_complete(ieee);
			} else {
				/* aid could not been allocated */
				ieee->softmac_stats.rx_ass_err++;
				printk("Association response status code 0x%x\n",
				       errcode);
				IEEE80211_DEBUG_MGMT("Association response status code 0x%x\n",
						     errcode);
				if (ieee->AsocRetryCount < RT_ASOC_RETRY_LIMIT)
					schedule_work(&ieee->associate_procedure_wq);
				else
					ieee80211_associate_abort(ieee);
			}
		}
		break;

	case IEEE80211_STYPE_ASSOC_REQ:
	case IEEE80211_STYPE_REASSOC_REQ:
		if ((ieee->softmac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->iw_mode == IW_MODE_MASTER)
			ieee80211_rx_assoc_rq(ieee, skb);
		break;

	case IEEE80211_STYPE_AUTH:
		if (ieee->softmac_features & IEEE_SOFTMAC_ASSOCIATE) {
			if (ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATING
			    && ieee->iw_mode == IW_MODE_INFRA) {
				IEEE80211_DEBUG_MGMT("Received auth response");
				ieee80211_check_auth_response(ieee, skb);
			} else if (ieee->iw_mode == IW_MODE_MASTER) {
				ieee80211_rx_auth_rq(ieee, skb);
			}
		}
		break;

	case IEEE80211_STYPE_PROBE_REQ:
		if ((ieee->softmac_features & IEEE_SOFTMAC_PROBERS) &&
		    ((ieee->iw_mode == IW_MODE_ADHOC ||
		      ieee->iw_mode == IW_MODE_MASTER) &&
		     ieee->state == IEEE80211_LINKED)) {
			ieee80211_rx_probe_rq(ieee, skb);
		}
		break;

	case IEEE80211_STYPE_DISASSOC:
	case IEEE80211_STYPE_DEAUTH:
		/* FIXME for now repeat all the association procedure
		* both for disassociation and deauthentication
		*/
		if ((ieee->softmac_features & IEEE_SOFTMAC_ASSOCIATE) &&
		    ieee->state == IEEE80211_LINKED &&
		    ieee->iw_mode == IW_MODE_INFRA) {
			ieee->state = IEEE80211_ASSOCIATING;
			ieee->softmac_stats.reassoc++;

			notify_wx_assoc_event(ieee);
			//HTSetConnectBwMode(ieee, HT_CHANNEL_WIDTH_20, HT_EXTCHNL_OFFSET_NO_EXT);
			RemovePeerTS(ieee, header->addr2);
			schedule_work(&ieee->associate_procedure_wq);
		}
		break;
	case IEEE80211_STYPE_MANAGE_ACT:
		ieee80211_process_action(ieee, skb);
		break;
	default:
		return -1;
	}

	//dev_kfree_skb_any(skb);
	return 0;
}