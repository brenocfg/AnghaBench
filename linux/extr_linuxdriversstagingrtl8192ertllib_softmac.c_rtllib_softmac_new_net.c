#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char u8 ;
struct rtllib_network {int capability; scalar_t__ channel; scalar_t__ ssid_len; char* ssid; scalar_t__ hidden_ssid_len; char* hidden_ssid; int /*<<< orphan*/  bssid; } ;
struct TYPE_8__ {scalar_t__ bdSupportHT; } ;
struct TYPE_7__ {int supported; } ;
struct TYPE_9__ {scalar_t__ ssid_len; char* ssid; TYPE_2__ bssht; TYPE_1__ qos_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  mode; int /*<<< orphan*/  channel; int /*<<< orphan*/  bssid; } ;
struct rtllib_device {scalar_t__ state; scalar_t__ iw_mode; scalar_t__ ibss_maxjoin_chal; short wap_set; short ssid_set; int softmac_features; int modulation; int rate; int /*<<< orphan*/  dot11HTOperationalRateSet; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* SetWirelessMode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_3__ current_network; int /*<<< orphan*/  associate_procedure_wq; int /*<<< orphan*/  (* LedControlHandler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_6__* pHTInfo; scalar_t__ AsocRetryCount; scalar_t__ wmm_acm; scalar_t__ is_roaming; } ;
struct TYPE_10__ {int bCurrentHTSupport; int /*<<< orphan*/  bEnableHT; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HTResetIOTSetting (TYPE_6__*) ; 
 int /*<<< orphan*/  HTResetSelfAndSavePeerSetting (struct rtllib_device*,TYPE_3__*) ; 
 int /*<<< orphan*/  IEEE_B ; 
 int /*<<< orphan*/  IEEE_G ; 
 int IEEE_SOFTMAC_SCAN ; 
 int IW_ESSID_MAX_SIZE ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  LED_CTL_START_TO_LINK ; 
 scalar_t__ RTLLIB_ASSOCIATING ; 
 scalar_t__ RTLLIB_LINKED ; 
 scalar_t__ RTLLIB_NOLINK ; 
 int RTLLIB_OFDM_MODULATION ; 
 int WLAN_CAPABILITY_ESS ; 
 int WLAN_CAPABILITY_IBSS ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,struct rtllib_network*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ rtllib_act_scanning (struct rtllib_device*,int) ; 
 scalar_t__ rtllib_is_54g (TYPE_3__*) ; 
 int /*<<< orphan*/  rtllib_stop_scan_syncro (struct rtllib_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void rtllib_softmac_new_net(struct rtllib_device *ieee,
				   struct rtllib_network *net)
{
	u8 tmp_ssid[IW_ESSID_MAX_SIZE + 1];
	int tmp_ssid_len = 0;

	short apset, ssidset, ssidbroad, apmatch, ssidmatch;

	/* we are interested in new new only if we are not associated
	 * and we are not associating / authenticating
	 */
	if (ieee->state != RTLLIB_NOLINK)
		return;

	if ((ieee->iw_mode == IW_MODE_INFRA) && !(net->capability &
	    WLAN_CAPABILITY_ESS))
		return;

	if ((ieee->iw_mode == IW_MODE_ADHOC) && !(net->capability &
	     WLAN_CAPABILITY_IBSS))
		return;

	if ((ieee->iw_mode == IW_MODE_ADHOC) &&
	    (net->channel > ieee->ibss_maxjoin_chal))
		return;
	if (ieee->iw_mode == IW_MODE_INFRA || ieee->iw_mode == IW_MODE_ADHOC) {
		/* if the user specified the AP MAC, we need also the essid
		 * This could be obtained by beacons or, if the network does not
		 * broadcast it, it can be put manually.
		 */
		apset = ieee->wap_set;
		ssidset = ieee->ssid_set;
		ssidbroad =  !(net->ssid_len == 0 || net->ssid[0] == '\0');
		apmatch = (memcmp(ieee->current_network.bssid, net->bssid,
				  ETH_ALEN) == 0);
		if (!ssidbroad) {
			ssidmatch = (ieee->current_network.ssid_len ==
				    net->hidden_ssid_len) &&
				    (!strncmp(ieee->current_network.ssid,
				    net->hidden_ssid, net->hidden_ssid_len));
			if (net->hidden_ssid_len > 0) {
				strncpy(net->ssid, net->hidden_ssid,
					net->hidden_ssid_len);
				net->ssid_len = net->hidden_ssid_len;
				ssidbroad = 1;
			}
		} else
			ssidmatch =
			   (ieee->current_network.ssid_len == net->ssid_len) &&
			   (!strncmp(ieee->current_network.ssid, net->ssid,
			   net->ssid_len));

		/* if the user set the AP check if match.
		 * if the network does not broadcast essid we check the
		 *	 user supplied ANY essid
		 * if the network does broadcast and the user does not set
		 *	 essid it is OK
		 * if the network does broadcast and the user did set essid
		 * check if essid match
		 * if the ap is not set, check that the user set the bssid
		 * and the network does broadcast and that those two bssid match
		 */
		if ((apset && apmatch &&
		   ((ssidset && ssidbroad && ssidmatch) ||
		   (ssidbroad && !ssidset) || (!ssidbroad && ssidset))) ||
		   (!apset && ssidset && ssidbroad && ssidmatch) ||
		   (ieee->is_roaming && ssidset && ssidbroad && ssidmatch)) {
			/* if the essid is hidden replace it with the
			 * essid provided by the user.
			 */
			if (!ssidbroad) {
				strncpy(tmp_ssid, ieee->current_network.ssid,
					IW_ESSID_MAX_SIZE);
				tmp_ssid_len = ieee->current_network.ssid_len;
			}
			memcpy(&ieee->current_network, net,
			       sizeof(struct rtllib_network));
			if (!ssidbroad) {
				strncpy(ieee->current_network.ssid, tmp_ssid,
					IW_ESSID_MAX_SIZE);
				ieee->current_network.ssid_len = tmp_ssid_len;
			}
			netdev_info(ieee->dev,
				    "Linking with %s,channel:%d, qos:%d, myHT:%d, networkHT:%d, mode:%x cur_net.flags:0x%x\n",
				    ieee->current_network.ssid,
				    ieee->current_network.channel,
				    ieee->current_network.qos_data.supported,
				    ieee->pHTInfo->bEnableHT,
				    ieee->current_network.bssht.bdSupportHT,
				    ieee->current_network.mode,
				    ieee->current_network.flags);

			if ((rtllib_act_scanning(ieee, false)) &&
			   !(ieee->softmac_features & IEEE_SOFTMAC_SCAN))
				rtllib_stop_scan_syncro(ieee);

			HTResetIOTSetting(ieee->pHTInfo);
			ieee->wmm_acm = 0;
			if (ieee->iw_mode == IW_MODE_INFRA) {
				/* Join the network for the first time */
				ieee->AsocRetryCount = 0;
				if ((ieee->current_network.qos_data.supported == 1) &&
				    ieee->current_network.bssht.bdSupportHT)
					HTResetSelfAndSavePeerSetting(ieee,
						 &(ieee->current_network));
				else
					ieee->pHTInfo->bCurrentHTSupport =
								 false;

				ieee->state = RTLLIB_ASSOCIATING;
				if (ieee->LedControlHandler != NULL)
					ieee->LedControlHandler(ieee->dev,
							 LED_CTL_START_TO_LINK);
				schedule_delayed_work(
					   &ieee->associate_procedure_wq, 0);
			} else {
				if (rtllib_is_54g(&ieee->current_network) &&
				    (ieee->modulation &
				     RTLLIB_OFDM_MODULATION)) {
					ieee->rate = 108;
					ieee->SetWirelessMode(ieee->dev,
							      IEEE_G);
					netdev_info(ieee->dev,
						    "Using G rates\n");
				} else {
					ieee->rate = 22;
					ieee->SetWirelessMode(ieee->dev,
							      IEEE_B);
					netdev_info(ieee->dev,
						    "Using B rates\n");
				}
				memset(ieee->dot11HTOperationalRateSet, 0, 16);
				ieee->state = RTLLIB_LINKED;
			}
		}
	}
}