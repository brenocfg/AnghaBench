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
struct dpaa2_eth_priv {int num_channels; TYPE_1__** channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  store; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpaa2_io_store_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_rings(struct dpaa2_eth_priv *priv)
{
	int i;

	for (i = 0; i < priv->num_channels; i++)
		dpaa2_io_store_destroy(priv->channel[i]->store);
}