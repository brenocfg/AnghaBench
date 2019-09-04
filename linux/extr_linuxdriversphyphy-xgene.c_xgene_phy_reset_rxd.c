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
struct xgene_phy_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXTX_REG7 ; 
 int /*<<< orphan*/  RXTX_REG7_RESETB_RXD_MASK ; 
 int /*<<< orphan*/  serdes_clrbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serdes_setbits (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void xgene_phy_reset_rxd(struct xgene_phy_ctx *ctx, int lane)
{
	/* Reset digital Rx */
	serdes_clrbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
	/* As per PHY design spec, the reset requires a minimum of 100us. */
	usleep_range(100, 150);
	serdes_setbits(ctx, lane, RXTX_REG7, RXTX_REG7_RESETB_RXD_MASK);
}