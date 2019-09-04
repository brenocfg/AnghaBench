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
typedef  int u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ar5523* priv; } ;
struct ieee80211_bss_conf {scalar_t__ assoc; } ;
struct ar5523 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; int /*<<< orphan*/  stat_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5523_CONNECTED ; 
 int BSS_CHANGED_ASSOC ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  UATH_LED_LINK ; 
 int /*<<< orphan*/  UATH_LED_OFF ; 
 int /*<<< orphan*/  UATH_LED_ON ; 
 int ar5523_create_connection (struct ar5523*,struct ieee80211_vif*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  ar5523_err (struct ar5523*,char*) ; 
 int ar5523_set_basic_rates (struct ar5523*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  ar5523_set_ledsteady (struct ar5523*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ar5523_write_associd (struct ar5523*,struct ieee80211_bss_conf*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ar5523_bss_info_changed(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif,
				    struct ieee80211_bss_conf *bss,
				    u32 changed)
{
	struct ar5523 *ar = hw->priv;
	int error;

	ar5523_dbg(ar, "bss_info_changed called\n");
	mutex_lock(&ar->mutex);

	if (!(changed & BSS_CHANGED_ASSOC))
		goto out_unlock;

	if (bss->assoc) {
		error = ar5523_create_connection(ar, vif, bss);
		if (error) {
			ar5523_err(ar, "could not create connection\n");
			goto out_unlock;
		}

		error = ar5523_set_basic_rates(ar, bss);
		if (error) {
			ar5523_err(ar, "could not set negotiated rate set\n");
			goto out_unlock;
		}

		error = ar5523_write_associd(ar, bss);
		if (error) {
			ar5523_err(ar, "could not set association\n");
			goto out_unlock;
		}

		/* turn link LED on */
		ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_ON);
		set_bit(AR5523_CONNECTED, &ar->flags);
		ieee80211_queue_delayed_work(hw, &ar->stat_work, HZ);

	} else {
		cancel_delayed_work(&ar->stat_work);
		clear_bit(AR5523_CONNECTED, &ar->flags);
		ar5523_set_ledsteady(ar, UATH_LED_LINK, UATH_LED_OFF);
	}

out_unlock:
	mutex_unlock(&ar->mutex);

}