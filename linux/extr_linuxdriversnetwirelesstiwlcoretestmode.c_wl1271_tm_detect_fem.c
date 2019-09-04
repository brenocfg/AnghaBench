#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl1271 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  fem_manuf; TYPE_1__* hw; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PLT_FEM_DETECT ; 
 int /*<<< orphan*/  WL1271_TM_ATTR_DATA ; 
 struct sk_buff* cfg80211_testmode_alloc_reply_skb (int /*<<< orphan*/ ,int) ; 
 int cfg80211_testmode_reply (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int nla_total_size (int) ; 
 int wl1271_plt_start (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_plt_stop (struct wl1271*) ; 

__attribute__((used)) static int wl1271_tm_detect_fem(struct wl1271 *wl, struct nlattr *tb[])
{
	/* return FEM type */
	int ret, len;
	struct sk_buff *skb;

	ret = wl1271_plt_start(wl, PLT_FEM_DETECT);
	if (ret < 0)
		goto out;

	mutex_lock(&wl->mutex);

	len = nla_total_size(sizeof(wl->fem_manuf));
	skb = cfg80211_testmode_alloc_reply_skb(wl->hw->wiphy, len);
	if (!skb) {
		ret = -ENOMEM;
		goto out_mutex;
	}

	if (nla_put(skb, WL1271_TM_ATTR_DATA, sizeof(wl->fem_manuf),
					      &wl->fem_manuf)) {
		kfree_skb(skb);
		ret = -EMSGSIZE;
		goto out_mutex;
	}

	ret = cfg80211_testmode_reply(skb);

out_mutex:
	mutex_unlock(&wl->mutex);

	/* We always stop plt after DETECT mode */
	wl1271_plt_stop(wl);
out:
	return ret;
}