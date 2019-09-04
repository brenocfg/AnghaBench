#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sxgbe_priv_data {int /*<<< orphan*/  ioaddr; TYPE_2__* hw; int /*<<< orphan*/  tx_path_in_lpi_mode; } ;
struct TYPE_4__ {TYPE_1__* mac; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_eee_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sxgbe_enable_eee_mode(const struct sxgbe_priv_data *priv)
{
	/* Check and enter in LPI mode */
	if (!priv->tx_path_in_lpi_mode)
		priv->hw->mac->set_eee_mode(priv->ioaddr);
}