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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_1__ isif_cfg; } ;
struct vpfe_isif_cul {int hcpat_even; int hcpat_odd; int vcpat; int en_lpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CULH ; 
 int CULL_PAT_EVEN_LINE_SHIFT ; 
 int /*<<< orphan*/  CULV ; 
 int ISIF_LPF_MASK ; 
 int ISIF_LPF_SHIFT ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  isif_merge (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isif_config_culling(struct vpfe_isif_device *isif, struct vpfe_isif_cul *cul)
{
	u32 val;

	/* Horizontal pattern */
	val = cul->hcpat_even << CULL_PAT_EVEN_LINE_SHIFT;
	val |= cul->hcpat_odd;
	isif_write(isif->isif_cfg.base_addr, val, CULH);
	/* vertical pattern */
	isif_write(isif->isif_cfg.base_addr, cul->vcpat, CULV);
	/* LPF */
	isif_merge(isif->isif_cfg.base_addr, ISIF_LPF_MASK << ISIF_LPF_SHIFT,
		   cul->en_lpf << ISIF_LPF_SHIFT, MODESET);
}