#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* coeff; int /*<<< orphan*/  en; } ;
struct vpfe_isif_df_csc {int start_pix; int num_pixels; int start_line; int num_lines; TYPE_2__ csc; } ;
struct TYPE_6__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_3__ isif_cfg; } ;
struct TYPE_4__ {int integer; int decimal; } ;

/* Variables and functions */
 scalar_t__ CSCCTL ; 
 scalar_t__ CSCM0 ; 
 scalar_t__ FMTLNH ; 
 scalar_t__ FMTLNV ; 
 scalar_t__ FMTSLV ; 
 scalar_t__ FMTSPH ; 
 int ISIF_CSCM_MSB_SHIFT ; 
 int ISIF_CSC_COEF_DECIMAL_MASK ; 
 int ISIF_CSC_COEF_INTEG_MASK ; 
 int ISIF_CSC_COEF_INTEG_SHIFT ; 
 int ISIF_DF_CSC_SPH_MASK ; 
 int VPFE_ISIF_CSC_NUM_COEFF ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void
isif_config_csc(struct vpfe_isif_device *isif, struct vpfe_isif_df_csc *df_csc)
{
	u32 val1;
	u32 val2;
	u32 i;

	if (!df_csc->csc.en) {
		isif_write(isif->isif_cfg.base_addr, 0, CSCCTL);
		return;
	}
	/* initialize all bits to 0 */
	val1 = 0;
	for (i = 0; i < VPFE_ISIF_CSC_NUM_COEFF; i++) {
		if ((i % 2) == 0) {
			/* CSCM - LSB */
			val1 = ((df_csc->csc.coeff[i].integer &
				ISIF_CSC_COEF_INTEG_MASK) <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				((df_csc->csc.coeff[i].decimal &
				ISIF_CSC_COEF_DECIMAL_MASK));
		} else {

			/* CSCM - MSB */
			val2 = ((df_csc->csc.coeff[i].integer &
				ISIF_CSC_COEF_INTEG_MASK) <<
				ISIF_CSC_COEF_INTEG_SHIFT) |
				((df_csc->csc.coeff[i].decimal &
				ISIF_CSC_COEF_DECIMAL_MASK));
			val2 <<= ISIF_CSCM_MSB_SHIFT;
			val2 |= val1;
			isif_write(isif->isif_cfg.base_addr, val2,
				   (CSCM0 + ((i-1) << 1)));
		}
	}
	/* program the active area */
	isif_write(isif->isif_cfg.base_addr, df_csc->start_pix &
		ISIF_DF_CSC_SPH_MASK, FMTSPH);
	/*
	 * one extra pixel as required for CSC. Actually number of
	 * pixel - 1 should be configured in this register. So we
	 * need to subtract 1 before writing to FMTSPH, but we will
	 * not do this since csc requires one extra pixel
	 */
	isif_write(isif->isif_cfg.base_addr, df_csc->num_pixels &
		ISIF_DF_CSC_SPH_MASK, FMTLNH);
	isif_write(isif->isif_cfg.base_addr, df_csc->start_line &
		ISIF_DF_CSC_SPH_MASK, FMTSLV);
	/*
	 * one extra line as required for CSC. See reason documented for
	 * num_pixels
	 */
	isif_write(isif->isif_cfg.base_addr, df_csc->num_lines &
		ISIF_DF_CSC_SPH_MASK, FMTLNV);
	/* Enable CSC */
	isif_write(isif->isif_cfg.base_addr, 1, CSCCTL);
}