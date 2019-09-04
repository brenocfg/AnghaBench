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
struct stmmac_priv {int tx_path_in_lpi_mode; int /*<<< orphan*/  eee_ctrl_timer; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmmac_reset_eee_mode (struct stmmac_priv*,int /*<<< orphan*/ ) ; 

void stmmac_disable_eee_mode(struct stmmac_priv *priv)
{
	stmmac_reset_eee_mode(priv, priv->hw);
	del_timer_sync(&priv->eee_ctrl_timer);
	priv->tx_path_in_lpi_mode = false;
}