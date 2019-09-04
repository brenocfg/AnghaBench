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
struct xgene_phy_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  serdes_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdes_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void serdes_setbits(struct xgene_phy_ctx *ctx, int lane, u32 reg,
			   u32 bits)
{
	u32 val;

	serdes_rd(ctx, lane, reg, &val);
	val |= bits;
	serdes_wr(ctx, lane, reg, val);
}