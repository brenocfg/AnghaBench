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
typedef  int /*<<< orphan*/  u32 ;
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; } ;
struct dpaa2_eth_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ drain_channel (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*) ; 

__attribute__((used)) static u32 drain_ingress_frames(struct dpaa2_eth_priv *priv)
{
	struct dpaa2_eth_channel *ch;
	int i;
	u32 drained = 0;

	for (i = 0; i < priv->num_channels; i++) {
		ch = priv->channel[i];
		drained += drain_channel(priv, ch);
	}

	return drained;
}