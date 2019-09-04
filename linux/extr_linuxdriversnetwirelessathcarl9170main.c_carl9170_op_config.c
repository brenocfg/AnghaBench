#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int /*<<< orphan*/  chan; } ;
struct TYPE_6__ {TYPE_5__ chandef; } ;
struct ieee80211_hw {TYPE_1__ conf; struct ar9170* priv; } ;
struct ar9170 {int /*<<< orphan*/  mutex; TYPE_4__* hw; } ;
typedef  enum nl80211_channel_type { ____Placeholder_nl80211_channel_type } nl80211_channel_type ;
struct TYPE_7__ {int /*<<< orphan*/  chan; } ;
struct TYPE_8__ {TYPE_2__ chandef; } ;
struct TYPE_9__ {TYPE_3__ conf; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int IEEE80211_CONF_CHANGE_LISTEN_INTERVAL ; 
 int IEEE80211_CONF_CHANGE_POWER ; 
 int IEEE80211_CONF_CHANGE_PS ; 
 int IEEE80211_CONF_CHANGE_SMPS ; 
 int carl9170_ps_update (struct ar9170*) ; 
 int carl9170_set_channel (struct ar9170*,int /*<<< orphan*/ ,int) ; 
 int carl9170_set_dyn_sifs_ack (struct ar9170*) ; 
 int carl9170_set_mac_tpc (struct ar9170*,int /*<<< orphan*/ ) ; 
 int carl9170_set_rts_cts_rate (struct ar9170*) ; 
 int carl9170_set_slot_time (struct ar9170*) ; 
 int carl9170_update_survey (struct ar9170*,int,int) ; 
 int cfg80211_get_chandef_type (TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carl9170_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct ar9170 *ar = hw->priv;
	int err = 0;

	mutex_lock(&ar->mutex);
	if (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL) {
		/* TODO */
		err = 0;
	}

	if (changed & IEEE80211_CONF_CHANGE_PS) {
		err = carl9170_ps_update(ar);
		if (err)
			goto out;
	}

	if (changed & IEEE80211_CONF_CHANGE_SMPS) {
		/* TODO */
		err = 0;
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		enum nl80211_channel_type channel_type =
			cfg80211_get_chandef_type(&hw->conf.chandef);

		/* adjust slot time for 5 GHz */
		err = carl9170_set_slot_time(ar);
		if (err)
			goto out;

		err = carl9170_update_survey(ar, true, false);
		if (err)
			goto out;

		err = carl9170_set_channel(ar, hw->conf.chandef.chan,
					   channel_type);
		if (err)
			goto out;

		err = carl9170_update_survey(ar, false, true);
		if (err)
			goto out;

		err = carl9170_set_dyn_sifs_ack(ar);
		if (err)
			goto out;

		err = carl9170_set_rts_cts_rate(ar);
		if (err)
			goto out;
	}

	if (changed & IEEE80211_CONF_CHANGE_POWER) {
		err = carl9170_set_mac_tpc(ar, ar->hw->conf.chandef.chan);
		if (err)
			goto out;
	}

out:
	mutex_unlock(&ar->mutex);
	return err;
}