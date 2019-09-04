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
struct wilc_wfi_p2p_listen_params {scalar_t__ listen_session_id; int /*<<< orphan*/  listen_ch; int /*<<< orphan*/  listen_cookie; } ;
struct wilc_priv {int p2p_listen_state; int /*<<< orphan*/  wdev; struct wilc_wfi_p2p_listen_params remain_on_ch_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_remain_on_channel_expired (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wilc_wfi_remain_on_channel_expired(void *data, u32 session_id)
{
	struct wilc_priv *priv = data;
	struct wilc_wfi_p2p_listen_params *params = &priv->remain_on_ch_params;

	if (session_id != params->listen_session_id)
		return;

	priv->p2p_listen_state = false;

	cfg80211_remain_on_channel_expired(priv->wdev, params->listen_cookie,
					   params->listen_ch, GFP_KERNEL);
}