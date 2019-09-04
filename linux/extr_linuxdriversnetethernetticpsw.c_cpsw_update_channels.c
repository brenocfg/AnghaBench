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
struct ethtool_channels {int /*<<< orphan*/  tx_count; int /*<<< orphan*/  rx_count; } ;
struct cpsw_priv {int dummy; } ;

/* Variables and functions */
 int cpsw_update_channels_res (struct cpsw_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpsw_update_channels(struct cpsw_priv *priv,
				struct ethtool_channels *ch)
{
	int ret;

	ret = cpsw_update_channels_res(priv, ch->rx_count, 1);
	if (ret)
		return ret;

	ret = cpsw_update_channels_res(priv, ch->tx_count, 0);
	if (ret)
		return ret;

	return 0;
}