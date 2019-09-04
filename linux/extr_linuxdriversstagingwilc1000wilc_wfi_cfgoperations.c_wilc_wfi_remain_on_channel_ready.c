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
struct TYPE_2__ {int /*<<< orphan*/  listen_duration; int /*<<< orphan*/  listen_ch; int /*<<< orphan*/  listen_cookie; } ;
struct wilc_priv {int p2p_listen_state; TYPE_1__ remain_on_ch_params; int /*<<< orphan*/  wdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_ready_on_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wilc_wfi_remain_on_channel_ready(void *priv_data)
{
	struct wilc_priv *priv;

	priv = priv_data;

	priv->p2p_listen_state = true;

	cfg80211_ready_on_channel(priv->wdev,
				  priv->remain_on_ch_params.listen_cookie,
				  priv->remain_on_ch_params.listen_ch,
				  priv->remain_on_ch_params.listen_duration,
				  GFP_KERNEL);
}