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
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  nctx; int /*<<< orphan*/  dpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_io_service_deregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_channel (struct dpaa2_eth_priv*,struct dpaa2_eth_channel*) ; 

__attribute__((used)) static void free_dpio(struct dpaa2_eth_priv *priv)
{
	int i;
	struct dpaa2_eth_channel *ch;

	/* deregister CDAN notifications and free channels */
	for (i = 0; i < priv->num_channels; i++) {
		ch = priv->channel[i];
		dpaa2_io_service_deregister(ch->dpio, &ch->nctx);
		free_channel(priv, ch);
	}
}