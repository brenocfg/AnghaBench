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
struct fsl_elbc_gpcm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void setup_periph(struct fsl_elbc_gpcm *priv,
				   const char *type)
{
#ifdef CONFIG_UIO_FSL_ELBC_GPCM_NETX5152
	if (strcmp(type, "netx5152") == 0) {
		priv->irq_handler = netx5152_irq_handler;
		priv->init = netx5152_init;
		priv->shutdown = netx5152_shutdown;
		priv->name = "netX 51/52";
		return;
	}
#endif
}