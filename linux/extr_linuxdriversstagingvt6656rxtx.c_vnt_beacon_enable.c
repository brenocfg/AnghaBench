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
struct vnt_private {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  beacon_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_REG_TCR ; 
 int /*<<< orphan*/  MAC_REG_TFTCTL ; 
 int /*<<< orphan*/  TCR_AUTOBCNTX ; 
 int /*<<< orphan*/  TFTCTL_TSFCNTREN ; 
 int vnt_beacon_make (struct vnt_private*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  vnt_clear_current_tsf (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_off (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_reg_bits_on (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_mac_set_beacon_interval (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_reset_next_tbtt (struct vnt_private*,int /*<<< orphan*/ ) ; 

int vnt_beacon_enable(struct vnt_private *priv, struct ieee80211_vif *vif,
		      struct ieee80211_bss_conf *conf)
{
	vnt_mac_reg_bits_off(priv, MAC_REG_TCR, TCR_AUTOBCNTX);

	vnt_mac_reg_bits_off(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	vnt_mac_set_beacon_interval(priv, conf->beacon_int);

	vnt_clear_current_tsf(priv);

	vnt_mac_reg_bits_on(priv, MAC_REG_TFTCTL, TFTCTL_TSFCNTREN);

	vnt_reset_next_tbtt(priv, conf->beacon_int);

	return vnt_beacon_make(priv, vif);
}