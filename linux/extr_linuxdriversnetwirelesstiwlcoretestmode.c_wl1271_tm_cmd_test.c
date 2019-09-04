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
typedef  scalar_t__ u8 ;
struct wl1271_command {int dummy; } ;
struct TYPE_3__ {scalar_t__ id; } ;
struct wl1271_cmd_cal_p2g {TYPE_1__ test; int /*<<< orphan*/  radio_status; } ;
struct wl1271 {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; TYPE_2__* hw; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
typedef  int s16 ;
struct TYPE_4__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TESTMODE ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 scalar_t__ TEST_CMD_P2G_CAL ; 
 size_t WL1271_TM_ATTR_ANSWER ; 
 size_t WL1271_TM_ATTR_DATA ; 
 scalar_t__ WLCORE_STATE_ON ; 
 struct sk_buff* cfg80211_testmode_alloc_reply_skb (int /*<<< orphan*/ ,int) ; 
 int cfg80211_testmode_reply (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* nla_data (struct nlattr*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 scalar_t__ nla_put (struct sk_buff*,size_t,int,void*) ; 
 int nla_total_size (int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int wl1271_cmd_test (struct wl1271*,void*,int,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1271_info (char*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 

__attribute__((used)) static int wl1271_tm_cmd_test(struct wl1271 *wl, struct nlattr *tb[])
{
	int buf_len, ret, len;
	struct sk_buff *skb;
	void *buf;
	u8 answer = 0;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd test");

	if (!tb[WL1271_TM_ATTR_DATA])
		return -EINVAL;

	buf = nla_data(tb[WL1271_TM_ATTR_DATA]);
	buf_len = nla_len(tb[WL1271_TM_ATTR_DATA]);

	if (tb[WL1271_TM_ATTR_ANSWER])
		answer = nla_get_u8(tb[WL1271_TM_ATTR_ANSWER]);

	if (buf_len > sizeof(struct wl1271_command))
		return -EMSGSIZE;

	mutex_lock(&wl->mutex);

	if (unlikely(wl->state != WLCORE_STATE_ON)) {
		ret = -EINVAL;
		goto out;
	}

	ret = pm_runtime_get_sync(wl->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(wl->dev);
		goto out;
	}

	ret = wl1271_cmd_test(wl, buf, buf_len, answer);
	if (ret < 0) {
		wl1271_warning("testmode cmd test failed: %d", ret);
		goto out_sleep;
	}

	if (answer) {
		/* If we got bip calibration answer print radio status */
		struct wl1271_cmd_cal_p2g *params =
			(struct wl1271_cmd_cal_p2g *) buf;

		s16 radio_status = (s16) le16_to_cpu(params->radio_status);

		if (params->test.id == TEST_CMD_P2G_CAL &&
		    radio_status < 0)
			wl1271_warning("testmode cmd: radio status=%d",
					radio_status);
		else
			wl1271_info("testmode cmd: radio status=%d",
					radio_status);

		len = nla_total_size(buf_len);
		skb = cfg80211_testmode_alloc_reply_skb(wl->hw->wiphy, len);
		if (!skb) {
			ret = -ENOMEM;
			goto out_sleep;
		}

		if (nla_put(skb, WL1271_TM_ATTR_DATA, buf_len, buf)) {
			kfree_skb(skb);
			ret = -EMSGSIZE;
			goto out_sleep;
		}

		ret = cfg80211_testmode_reply(skb);
		if (ret < 0)
			goto out_sleep;
	}

out_sleep:
	pm_runtime_mark_last_busy(wl->dev);
	pm_runtime_put_autosuspend(wl->dev);
out:
	mutex_unlock(&wl->mutex);

	return ret;
}