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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct vnt_private {int byPreambleType; int bShortSlotTime; scalar_t__ op_mode; scalar_t__ PortOffset; TYPE_3__* pcid; int /*<<< orphan*/  wCurrentRate; int /*<<< orphan*/ * abyBBVGA; int /*<<< orphan*/  byBBType; int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  lock; int /*<<< orphan*/  current_aid; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  sync_tsf; TYPE_4__* beacon_rate; scalar_t__ assoc; int /*<<< orphan*/  enable_beacon; TYPE_2__ chandef; scalar_t__ use_short_slot; scalar_t__ use_cts_prot; scalar_t__ use_short_preamble; int /*<<< orphan*/  basic_rates; scalar_t__ bssid; int /*<<< orphan*/  aid; } ;
struct TYPE_8__ {int /*<<< orphan*/  hw_value; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBvSetVGAGainOffset (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INFO ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_CTS_PROT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int BSS_CHANGED_TXPOWER ; 
 int /*<<< orphan*/  CARDbSetBeaconPeriod (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDbSetPhyParameter (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDbUpdateTSF (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDvSetFirstNextTBTT (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARDvUpdateBasicTopRate (struct vnt_private*) ; 
 int /*<<< orphan*/  MAC_REG_TCR ; 
 scalar_t__ MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  MACvDisableBarkerPreambleMd (scalar_t__) ; 
 int /*<<< orphan*/  MACvDisableProtectMD (scalar_t__) ; 
 int /*<<< orphan*/  MACvEnableBarkerPreambleMd (scalar_t__) ; 
 int /*<<< orphan*/  MACvEnableProtectMD (scalar_t__) ; 
 int /*<<< orphan*/  MACvRegBitsOff (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRegBitsOn (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWriteBSSIDAddress (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  RFbSetPower (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTREN ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTRST ; 
 int /*<<< orphan*/  VNSvOutPortB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vnt_beacon_enable (struct vnt_private*,struct ieee80211_vif*,struct ieee80211_bss_conf*) ; 

__attribute__((used)) static void vnt_bss_info_changed(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_bss_conf *conf, u32 changed)
{
	struct vnt_private *priv = hw->priv;

	priv->current_aid = conf->aid;

	if (changed & BSS_CHANGED_BSSID && conf->bssid) {
		unsigned long flags;

		spin_lock_irqsave(&priv->lock, flags);

		MACvWriteBSSIDAddress(priv->PortOffset, (u8 *)conf->bssid);

		spin_unlock_irqrestore(&priv->lock, flags);
	}

	if (changed & BSS_CHANGED_BASIC_RATES) {
		priv->basic_rates = conf->basic_rates;

		CARDvUpdateBasicTopRate(priv);

		dev_dbg(&priv->pcid->dev,
			"basic rates %x\n", conf->basic_rates);
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		if (conf->use_short_preamble) {
			MACvEnableBarkerPreambleMd(priv->PortOffset);
			priv->byPreambleType = true;
		} else {
			MACvDisableBarkerPreambleMd(priv->PortOffset);
			priv->byPreambleType = false;
		}
	}

	if (changed & BSS_CHANGED_ERP_CTS_PROT) {
		if (conf->use_cts_prot)
			MACvEnableProtectMD(priv->PortOffset);
		else
			MACvDisableProtectMD(priv->PortOffset);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		if (conf->use_short_slot)
			priv->bShortSlotTime = true;
		else
			priv->bShortSlotTime = false;

		CARDbSetPhyParameter(priv, priv->byBBType);
		BBvSetVGAGainOffset(priv, priv->abyBBVGA[0]);
	}

	if (changed & BSS_CHANGED_TXPOWER)
		RFbSetPower(priv, priv->wCurrentRate,
			    conf->chandef.chan->hw_value);

	if (changed & BSS_CHANGED_BEACON_ENABLED) {
		dev_dbg(&priv->pcid->dev,
			"Beacon enable %d\n", conf->enable_beacon);

		if (conf->enable_beacon) {
			vnt_beacon_enable(priv, vif, conf);

			MACvRegBitsOn(priv->PortOffset, MAC_REG_TCR,
				      TCR_AUTOBCNTX);
		} else {
			MACvRegBitsOff(priv->PortOffset, MAC_REG_TCR,
				       TCR_AUTOBCNTX);
		}
	}

	if (changed & (BSS_CHANGED_ASSOC | BSS_CHANGED_BEACON_INFO) &&
	    priv->op_mode != NL80211_IFTYPE_AP) {
		if (conf->assoc && conf->beacon_rate) {
			CARDbUpdateTSF(priv, conf->beacon_rate->hw_value,
				       conf->sync_tsf);

			CARDbSetBeaconPeriod(priv, conf->beacon_int);

			CARDvSetFirstNextTBTT(priv, conf->beacon_int);
		} else {
			VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL,
				     TFTCTL_TSFCNTRST);
			VNSvOutPortB(priv->PortOffset + MAC_REG_TFTCTL,
				     TFTCTL_TSFCNTREN);
		}
	}
}