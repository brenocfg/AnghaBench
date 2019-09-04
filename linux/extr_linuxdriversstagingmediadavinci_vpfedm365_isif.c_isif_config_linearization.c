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
typedef  int u32 ;
struct TYPE_3__ {int integer; int decimal; } ;
struct vpfe_isif_linearize {int corr_shft; int* table; TYPE_1__ scale_fact; int /*<<< orphan*/  en; } ;
struct TYPE_4__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_2__ isif_cfg; } ;

/* Variables and functions */
 int ISIF_LIN_CORRSFT_MASK ; 
 int ISIF_LIN_CORRSFT_SHIFT ; 
 int ISIF_LIN_ENTRY_MASK ; 
 int ISIF_LIN_SCALE_FACT_DECIMAL_MASK ; 
 int ISIF_LIN_SCALE_FACT_INTEG_SHIFT ; 
 int /*<<< orphan*/  LINCFG0 ; 
 int /*<<< orphan*/  LINCFG1 ; 
 int VPFE_ISIF_LINEAR_TAB_SIZE ; 
 int /*<<< orphan*/  isif_regw_lin_tbl (struct vpfe_isif_device*,int,int,int) ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isif_config_linearization(struct vpfe_isif_device *isif,
			  struct vpfe_isif_linearize *linearize)
{
	u32 val;
	u32 i;

	if (!linearize->en) {
		isif_write(isif->isif_cfg.base_addr, 0, LINCFG0);
		return;
	}
	/* shift value for correction */
	val = (linearize->corr_shft & ISIF_LIN_CORRSFT_MASK) <<
	      ISIF_LIN_CORRSFT_SHIFT;
	/* enable */
	val |= 1;
	isif_write(isif->isif_cfg.base_addr, val, LINCFG0);
	/* Scale factor */
	val = (linearize->scale_fact.integer & 1) <<
	      ISIF_LIN_SCALE_FACT_INTEG_SHIFT;
	val |= linearize->scale_fact.decimal & ISIF_LIN_SCALE_FACT_DECIMAL_MASK;
	isif_write(isif->isif_cfg.base_addr, val, LINCFG1);

	for (i = 0; i < VPFE_ISIF_LINEAR_TAB_SIZE; i++) {
		val = linearize->table[i] & ISIF_LIN_ENTRY_MASK;
		if (i%2)
			isif_regw_lin_tbl(isif, val, ((i >> 1) << 2), 1);
		else
			isif_regw_lin_tbl(isif, val, ((i >> 1) << 2), 0);
	}
}