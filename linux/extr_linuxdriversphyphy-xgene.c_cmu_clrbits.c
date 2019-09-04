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
typedef  enum cmu_type_t { ____Placeholder_cmu_type_t } cmu_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  cmu_rd (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmu_wr (struct xgene_phy_ctx*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cmu_clrbits(struct xgene_phy_ctx *ctx, enum cmu_type_t cmu_type,
			u32 reg, u32 bits)
{
	u32 val;

	cmu_rd(ctx, cmu_type, reg, &val);
	val &= ~bits;
	cmu_wr(ctx, cmu_type, reg, val);
}