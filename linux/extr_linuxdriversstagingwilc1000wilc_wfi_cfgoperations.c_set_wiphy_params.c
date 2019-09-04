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
typedef  int u32 ;
struct wiphy {int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  retry_long; int /*<<< orphan*/  retry_short; } ;
struct wilc_vif {int dummy; } ;
struct wilc_priv {int /*<<< orphan*/  dev; } ;
struct cfg_param_attr {int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  flag; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  long_retry_limit; int /*<<< orphan*/  short_retry_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRAG_THRESHOLD ; 
 int /*<<< orphan*/  RETRY_LONG ; 
 int /*<<< orphan*/  RETRY_SHORT ; 
 int /*<<< orphan*/  RTS_THRESHOLD ; 
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RETRY_LONG ; 
 int WIPHY_PARAM_RETRY_SHORT ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct wilc_vif* netdev_priv (int /*<<< orphan*/ ) ; 
 int wilc_hif_set_cfg (struct wilc_vif*,struct cfg_param_attr*) ; 
 struct wilc_priv* wiphy_priv (struct wiphy*) ; 

__attribute__((used)) static int set_wiphy_params(struct wiphy *wiphy, u32 changed)
{
	int ret;
	struct cfg_param_attr cfg_param_val;
	struct wilc_priv *priv = wiphy_priv(wiphy);
	struct wilc_vif *vif = netdev_priv(priv->dev);

	cfg_param_val.flag = 0;

	if (changed & WIPHY_PARAM_RETRY_SHORT) {
		cfg_param_val.flag  |= RETRY_SHORT;
		cfg_param_val.short_retry_limit = wiphy->retry_short;
	}
	if (changed & WIPHY_PARAM_RETRY_LONG) {
		cfg_param_val.flag |= RETRY_LONG;
		cfg_param_val.long_retry_limit = wiphy->retry_long;
	}
	if (changed & WIPHY_PARAM_FRAG_THRESHOLD) {
		cfg_param_val.flag |= FRAG_THRESHOLD;
		cfg_param_val.frag_threshold = wiphy->frag_threshold;
	}

	if (changed & WIPHY_PARAM_RTS_THRESHOLD) {
		cfg_param_val.flag |= RTS_THRESHOLD;
		cfg_param_val.rts_threshold = wiphy->rts_threshold;
	}

	ret = wilc_hif_set_cfg(vif, &cfg_param_val);
	if (ret)
		netdev_err(priv->dev, "Error in setting WIPHY PARAMS\n");

	return ret;
}