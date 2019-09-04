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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_chanctx_conf {int dummy; } ;
struct ath10k_mac_change_chanctx_arg {size_t next_vif; size_t n_vifs; TYPE_1__* vifs; struct ieee80211_chanctx_conf* ctx; } ;
struct TYPE_2__ {struct ieee80211_chanctx_conf* new_ctx; struct ieee80211_chanctx_conf* old_ctx; struct ieee80211_vif* vif; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct ieee80211_chanctx_conf* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath10k_mac_change_chanctx_fill_iter(void *data, u8 *mac,
				    struct ieee80211_vif *vif)
{
	struct ath10k_mac_change_chanctx_arg *arg = data;
	struct ieee80211_chanctx_conf *ctx;

	ctx = rcu_access_pointer(vif->chanctx_conf);
	if (ctx != arg->ctx)
		return;

	if (WARN_ON(arg->next_vif == arg->n_vifs))
		return;

	arg->vifs[arg->next_vif].vif = vif;
	arg->vifs[arg->next_vif].old_ctx = ctx;
	arg->vifs[arg->next_vif].new_ctx = ctx;
	arg->next_vif++;
}