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
struct iwl_rxon_context {scalar_t__ vif; } ;
struct iwl_priv {int /*<<< orphan*/  status; struct iwl_rxon_context* contexts; } ;

/* Variables and functions */
 size_t IWL_RXON_CTX_BSS ; 
 int /*<<< orphan*/  STATUS_CHANNEL_SWITCH_PENDING ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  ieee80211_chswitch_done (scalar_t__,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_chswitch_done(struct iwl_priv *priv, bool is_success)
{
	/*
	 * MULTI-FIXME
	 * See iwlagn_mac_channel_switch.
	 */
	struct iwl_rxon_context *ctx = &priv->contexts[IWL_RXON_CTX_BSS];

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	if (!test_and_clear_bit(STATUS_CHANNEL_SWITCH_PENDING, &priv->status))
		return;

	if (ctx->vif)
		ieee80211_chswitch_done(ctx->vif, is_success);
}