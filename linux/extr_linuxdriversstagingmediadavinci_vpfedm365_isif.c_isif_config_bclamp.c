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
struct TYPE_6__ {int /*<<< orphan*/  base_addr; } ;
struct vpfe_isif_device {TYPE_3__ isif_cfg; } ;
struct TYPE_5__ {int ob_h_sz_calc; int reset_val_sel; int line_ave_coef; int reset_clamp_val; int ob_start_h; int ob_start_v; int ob_v_sz_calc; } ;
struct TYPE_4__ {int mode; int win_count_calc; int base_win_sel_calc; int clamp_pix_limit; int win_h_sz_calc; int win_v_sz_calc; int win_start_h_calc; int win_start_v_calc; } ;
struct vpfe_isif_black_clamp {int dc_offset; int bc_mode_color; int vert_start_sub; TYPE_2__ vert; TYPE_1__ horz; int /*<<< orphan*/  en; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAMPCFG ; 
 int /*<<< orphan*/  CLDCOFST ; 
 int /*<<< orphan*/  CLHWIN0 ; 
 int /*<<< orphan*/  CLHWIN1 ; 
 int /*<<< orphan*/  CLHWIN2 ; 
 int /*<<< orphan*/  CLSV ; 
 int /*<<< orphan*/  CLVRV ; 
 int /*<<< orphan*/  CLVWIN0 ; 
 int /*<<< orphan*/  CLVWIN1 ; 
 int /*<<< orphan*/  CLVWIN2 ; 
 int /*<<< orphan*/  CLVWIN3 ; 
 int ISIF_BC_DCOFFSET_MASK ; 
 int ISIF_BC_MODE_COLOR_MASK ; 
 int ISIF_BC_MODE_COLOR_SHIFT ; 
 int ISIF_BC_VERT_START_SUB_V_MASK ; 
 int ISIF_HORZ_BC_MODE_MASK ; 
 int ISIF_HORZ_BC_MODE_SHIFT ; 
 int ISIF_HORZ_BC_PIX_LIMIT_SHIFT ; 
 int ISIF_HORZ_BC_WIN_COUNT_MASK ; 
 int ISIF_HORZ_BC_WIN_H_SIZE_MASK ; 
 int ISIF_HORZ_BC_WIN_H_SIZE_SHIFT ; 
 int ISIF_HORZ_BC_WIN_SEL_SHIFT ; 
 int ISIF_HORZ_BC_WIN_START_H_MASK ; 
 int ISIF_HORZ_BC_WIN_START_V_MASK ; 
 int ISIF_HORZ_BC_WIN_V_SIZE_MASK ; 
 int ISIF_HORZ_BC_WIN_V_SIZE_SHIFT ; 
 int ISIF_VERT_BC_LINE_AVE_COEF_SHIFT ; 
 int ISIF_VERT_BC_OB_H_SZ_MASK ; 
 int ISIF_VERT_BC_OB_START_HORZ_MASK ; 
 int ISIF_VERT_BC_OB_START_VERT_MASK ; 
 int ISIF_VERT_BC_OB_VERT_SZ_MASK ; 
 int ISIF_VERT_BC_RST_VAL_MASK ; 
 int ISIF_VERT_BC_RST_VAL_SEL_MASK ; 
 int ISIF_VERT_BC_RST_VAL_SEL_SHIFT ; 
 int VPFE_ISIF_HORZ_BC_DISABLE ; 
 int VPFE_ISIF_VERT_BC_USE_CONFIG_CLAMP_VAL ; 
 int /*<<< orphan*/  isif_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_config_bclamp(struct vpfe_isif_device *isif,
		   struct vpfe_isif_black_clamp *bc)
{
	u32 val;

	/**
	 * DC Offset is always added to image data irrespective of bc enable
	 * status
	 */
	val = bc->dc_offset & ISIF_BC_DCOFFSET_MASK;
	isif_write(isif->isif_cfg.base_addr, val, CLDCOFST);

	if (!bc->en)
		return;

	val = (bc->bc_mode_color & ISIF_BC_MODE_COLOR_MASK) <<
		ISIF_BC_MODE_COLOR_SHIFT;

	/* Enable BC and horizontal clamp calculation paramaters */
	val = val | 1 | ((bc->horz.mode & ISIF_HORZ_BC_MODE_MASK) <<
	      ISIF_HORZ_BC_MODE_SHIFT);

	isif_write(isif->isif_cfg.base_addr, val, CLAMPCFG);

	if (bc->horz.mode != VPFE_ISIF_HORZ_BC_DISABLE) {
		/*
		 * Window count for calculation
		 * Base window selection
		 * pixel limit
		 * Horizontal size of window
		 * vertical size of the window
		 * Horizontal start position of the window
		 * Vertical start position of the window
		 */
		val = (bc->horz.win_count_calc & ISIF_HORZ_BC_WIN_COUNT_MASK) |
		      ((bc->horz.base_win_sel_calc & 1) <<
		      ISIF_HORZ_BC_WIN_SEL_SHIFT) |
		      ((bc->horz.clamp_pix_limit & 1) <<
		      ISIF_HORZ_BC_PIX_LIMIT_SHIFT) |
		      ((bc->horz.win_h_sz_calc &
		      ISIF_HORZ_BC_WIN_H_SIZE_MASK) <<
		      ISIF_HORZ_BC_WIN_H_SIZE_SHIFT) |
		      ((bc->horz.win_v_sz_calc &
		      ISIF_HORZ_BC_WIN_V_SIZE_MASK) <<
		      ISIF_HORZ_BC_WIN_V_SIZE_SHIFT);

		isif_write(isif->isif_cfg.base_addr, val, CLHWIN0);

		val = bc->horz.win_start_h_calc & ISIF_HORZ_BC_WIN_START_H_MASK;
		isif_write(isif->isif_cfg.base_addr, val, CLHWIN1);

		val = bc->horz.win_start_v_calc & ISIF_HORZ_BC_WIN_START_V_MASK;
		isif_write(isif->isif_cfg.base_addr, val, CLHWIN2);
	}

	/* vertical clamp calculation paramaters */
	/* OB H Valid */
	val = bc->vert.ob_h_sz_calc & ISIF_VERT_BC_OB_H_SZ_MASK;

	/* Reset clamp value sel for previous line */
	val |= (bc->vert.reset_val_sel & ISIF_VERT_BC_RST_VAL_SEL_MASK) <<
				ISIF_VERT_BC_RST_VAL_SEL_SHIFT;

	/* Line average coefficient */
	val |= bc->vert.line_ave_coef << ISIF_VERT_BC_LINE_AVE_COEF_SHIFT;
	isif_write(isif->isif_cfg.base_addr, val, CLVWIN0);

	/* Configured reset value */
	if (bc->vert.reset_val_sel == VPFE_ISIF_VERT_BC_USE_CONFIG_CLAMP_VAL) {
		val = bc->vert.reset_clamp_val & ISIF_VERT_BC_RST_VAL_MASK;
		isif_write(isif->isif_cfg.base_addr, val, CLVRV);
	}

	/* Optical Black horizontal start position */
	val = bc->vert.ob_start_h & ISIF_VERT_BC_OB_START_HORZ_MASK;
	isif_write(isif->isif_cfg.base_addr, val, CLVWIN1);

	/* Optical Black vertical start position */
	val = bc->vert.ob_start_v & ISIF_VERT_BC_OB_START_VERT_MASK;
	isif_write(isif->isif_cfg.base_addr, val, CLVWIN2);

	val = bc->vert.ob_v_sz_calc & ISIF_VERT_BC_OB_VERT_SZ_MASK;
	isif_write(isif->isif_cfg.base_addr, val, CLVWIN3);

	/* Vertical start position for BC subtraction */
	val = bc->vert_start_sub & ISIF_BC_VERT_START_SUB_V_MASK;
	isif_write(isif->isif_cfg.base_addr, val, CLSV);
}