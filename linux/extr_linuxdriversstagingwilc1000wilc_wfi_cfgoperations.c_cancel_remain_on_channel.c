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
typedef  int /*<<< orphan*/  u64 ;
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct wilc_vif {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  listen_session_id; } ;
struct wilc_priv {TYPE_1__ remain_on_ch_params; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_listen_state_expired (struct wilc_vif*,int /*<<< orphan*/ ) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int cancel_remain_on_channel(struct wiphy *wiphy,
				    struct wireless_dev *wdev,
				    u64 cookie)
{
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	return wilc_listen_state_expired(vif,
			priv->remain_on_ch_params.listen_session_id);
}