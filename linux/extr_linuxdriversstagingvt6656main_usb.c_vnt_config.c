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
typedef  int u32 ;
struct vnt_private {scalar_t__ bb_type; int /*<<< orphan*/  current_rate; } ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct ieee80211_conf {int flags; TYPE_2__ chandef; int /*<<< orphan*/  listen_interval; } ;
struct ieee80211_hw {struct ieee80211_conf conf; struct vnt_private* priv; } ;
struct TYPE_3__ {scalar_t__ band; int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 scalar_t__ BB_TYPE_11A ; 
 scalar_t__ BB_TYPE_11B ; 
 scalar_t__ BB_TYPE_11G ; 
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_OFFCHANNEL ; 
 int IEEE80211_CONF_PS ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RATE_1M ; 
 int /*<<< orphan*/  RATE_54M ; 
 int /*<<< orphan*/  vnt_disable_power_saving (struct vnt_private*) ; 
 int /*<<< orphan*/  vnt_enable_power_saving (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_rf_setpower (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnt_set_channel (struct vnt_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vnt_config(struct ieee80211_hw *hw, u32 changed)
{
	struct vnt_private *priv = hw->priv;
	struct ieee80211_conf *conf = &hw->conf;

	if (changed & IEEE80211_CONF_CHANGE_PS) {
		if (conf->flags & IEEE80211_CONF_PS)
			vnt_enable_power_saving(priv, conf->listen_interval);
		else
			vnt_disable_power_saving(priv);
	}

	if ((changed & IEEE80211_CONF_CHANGE_CHANNEL) ||
	    (conf->flags & IEEE80211_CONF_OFFCHANNEL)) {
		vnt_set_channel(priv, conf->chandef.chan->hw_value);

		if (conf->chandef.chan->band == NL80211_BAND_5GHZ)
			priv->bb_type = BB_TYPE_11A;
		else
			priv->bb_type = BB_TYPE_11G;
	}

	if (changed & IEEE80211_CONF_CHANGE_POWER) {
		if (priv->bb_type == BB_TYPE_11B)
			priv->current_rate = RATE_1M;
		else
			priv->current_rate = RATE_54M;

		vnt_rf_setpower(priv, priv->current_rate,
				conf->chandef.chan->hw_value);
	}

	return 0;
}