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
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int IEEE80211_CONF_CHANGE_CHANNEL ; 
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 
 int /*<<< orphan*/  ar5523_flush_tx (struct ar5523*) ; 
 int /*<<< orphan*/  ar5523_switch_chan (struct ar5523*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ar5523_hwconfig(struct ieee80211_hw *hw, u32 changed)
{
	struct ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "config called\n");
	mutex_lock(&ar->mutex);
	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		ar5523_dbg(ar, "Do channel switch\n");
		ar5523_flush_tx(ar);
		ar5523_switch_chan(ar);
	}
	mutex_unlock(&ar->mutex);
	return 0;
}