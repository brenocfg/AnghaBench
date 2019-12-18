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
struct ieee80211_vif {scalar_t__ type; } ;
struct TYPE_3__ {int /*<<< orphan*/  func_lock; int /*<<< orphan*/  function_inst_ids; } ;
struct TYPE_4__ {TYPE_1__ nan; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;
struct cfg80211_nan_match_params {int /*<<< orphan*/  cookie; int /*<<< orphan*/  inst_id; } ;
struct cfg80211_nan_func {int /*<<< orphan*/  cookie; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_NAN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_nan_match (int /*<<< orphan*/ ,struct cfg80211_nan_match_params*,int /*<<< orphan*/ ) ; 
 struct cfg80211_nan_func* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ieee80211_sub_if_data* vif_to_sdata (struct ieee80211_vif*) ; 

void ieee80211_nan_func_match(struct ieee80211_vif *vif,
			      struct cfg80211_nan_match_params *match,
			      gfp_t gfp)
{
	struct ieee80211_sub_if_data *sdata = vif_to_sdata(vif);
	struct cfg80211_nan_func *func;

	if (WARN_ON(vif->type != NL80211_IFTYPE_NAN))
		return;

	spin_lock_bh(&sdata->u.nan.func_lock);

	func = idr_find(&sdata->u.nan.function_inst_ids,  match->inst_id);
	if (WARN_ON(!func)) {
		spin_unlock_bh(&sdata->u.nan.func_lock);
		return;
	}
	match->cookie = func->cookie;

	spin_unlock_bh(&sdata->u.nan.func_lock);

	cfg80211_nan_match(ieee80211_vif_to_wdev(vif), match, gfp);
}