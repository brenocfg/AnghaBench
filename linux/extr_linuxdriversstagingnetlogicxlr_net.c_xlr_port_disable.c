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
struct xlr_net_priv {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int O_MAC_CONFIG_1__rxen ; 
 int O_MAC_CONFIG_1__rxfc ; 
 int O_MAC_CONFIG_1__txen ; 
 int O_MAC_CONFIG_1__txfc ; 
 int O_RX_CONTROL__RXENABLE ; 
 int O_TX_CONTROL__TXENABLE ; 
 int O_TX_CONTROL__TXTHRESHOLD ; 
 int /*<<< orphan*/  R_MAC_CONFIG_1 ; 
 int /*<<< orphan*/  R_RX_CONTROL ; 
 int /*<<< orphan*/  R_TX_CONTROL ; 
 int /*<<< orphan*/  xlr_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void xlr_port_disable(struct xlr_net_priv *priv)
{
	/* Setup MAC_CONFIG reg */
	/* Rx Tx disable*/
	xlr_reg_update(priv->base_addr, R_MAC_CONFIG_1,
		       ((1 << O_MAC_CONFIG_1__rxen) |
			(1 << O_MAC_CONFIG_1__txen) |
			(1 << O_MAC_CONFIG_1__rxfc) |
			(1 << O_MAC_CONFIG_1__txfc)), 0x0);

	/* Setup tx control reg */
	xlr_reg_update(priv->base_addr, R_TX_CONTROL,
		       ((1 << O_TX_CONTROL__TXENABLE) |
		       (512 << O_TX_CONTROL__TXTHRESHOLD)), 0);

	/* Setup rx control reg */
	xlr_reg_update(priv->base_addr, R_RX_CONTROL,
		       1 << O_RX_CONTROL__RXENABLE, 0);
}