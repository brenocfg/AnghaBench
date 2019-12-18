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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  func_lock; int /*<<< orphan*/  function_inst_ids; } ;
struct TYPE_4__ {TYPE_1__ nan; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct cfg80211_nan_func {int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum nl80211_nan_func_term_reason { ____Placeholder_nl80211_nan_func_term_reason } nl80211_nan_func_term_reason ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_NAN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_free_nan_func (struct cfg80211_nan_func*) ; 
 int /*<<< orphan*/  cfg80211_nan_func_terminated (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfg80211_nan_func* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_nan_func_terminated(struct ieee80211_vif *vif,
				   u8 inst_id,
				   enum nl80211_nan_func_term_reason reason,
				   gfp_t gfp)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct cfg80211_nan_func *func;
	u64 cookie;

	if (WARN_ON(vif->type != NL80211_IFTYPE_NAN))
		return;

	spin_lock_bh(&sdata->u.nan.func_lock);

	func = idr_find(&sdata->u.nan.function_inst_ids, inst_id);
	if (WARN_ON(!func)) {
		spin_unlock_bh(&sdata->u.nan.func_lock);
		return;
	}

	cookie = func->cookie;
	idr_remove(&sdata->u.nan.function_inst_ids, inst_id);

	spin_unlock_bh(&sdata->u.nan.func_lock);

	cfg80211_free_nan_func(func);

	cfg80211_nan_func_terminated(ieee80211_vif_to_wdev(vif), inst_id,
				     reason, cookie, gfp);
}