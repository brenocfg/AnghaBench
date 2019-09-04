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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wl1251 {int /*<<< orphan*/  mutex; } ;
struct ieee80211_hw {struct wl1251* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wl1251_acx_rts_threshold (struct wl1251*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1251_ps_elp_sleep (struct wl1251*) ; 
 int wl1251_ps_elp_wakeup (struct wl1251*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

__attribute__((used)) static int wl1251_op_set_rts_threshold(struct ieee80211_hw *hw, u32 value)
{
	struct wl1251 *wl = hw->priv;
	int ret;

	mutex_lock(&wl->mutex);

	ret = wl1251_ps_elp_wakeup(wl);
	if (ret < 0)
		goto out;

	ret = wl1251_acx_rts_threshold(wl, (u16) value);
	if (ret < 0)
		wl1251_warning("wl1251_op_set_rts_threshold failed: %d", ret);

	wl1251_ps_elp_sleep(wl);

out:
	mutex_unlock(&wl->mutex);

	return ret;
}