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
struct dpaa2_eth_priv {TYPE_1__* dpbp_dev; int /*<<< orphan*/  mc_io; } ;
struct TYPE_2__ {int /*<<< orphan*/  mc_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dpbp_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpbp_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drain_pool (struct dpaa2_eth_priv*) ; 
 int /*<<< orphan*/  fsl_mc_object_free (TYPE_1__*) ; 

__attribute__((used)) static void free_dpbp(struct dpaa2_eth_priv *priv)
{
	drain_pool(priv);
	dpbp_disable(priv->mc_io, 0, priv->dpbp_dev->mc_handle);
	dpbp_close(priv->mc_io, 0, priv->dpbp_dev->mc_handle);
	fsl_mc_object_free(priv->dpbp_dev);
}