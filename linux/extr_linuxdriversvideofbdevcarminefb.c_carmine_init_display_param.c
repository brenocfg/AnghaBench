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
struct carmine_fb {int smem_offset; TYPE_1__* res; } ;
struct TYPE_2__ {int hdp; int vdp; } ;

/* Variables and functions */
 int CARMINE_CURSOR0_PRIORITY_MASK ; 
 int CARMINE_CURSOR1_PRIORITY_MASK ; 
 int CARMINE_CURSOR_CUTZ_MASK ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L0 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L2 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L3 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L4 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L5 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L6 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_BLEND_MODE_L7 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_CUR1_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_CUR2_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_CURSOR_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_C_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_DISP_ADR ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_ORG_ADR ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L0_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_ORG_ADR ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_WIDTH ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L1_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_DISP_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L2_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_DISP_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L3_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_DISP_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L4_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_DISP_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L5_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_DISP_ADR0 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L6_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7PX ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7PY ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7RM ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_DISP_ADR0 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_DISP_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_EXT_MODE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_MODE_W_H ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_ORG_ADR1 ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_TRANS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_WIN_POS ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_L7_WIN_SIZE ; 
 int /*<<< orphan*/  CARMINE_DISP_REG_MLMR_TRANS ; 
 int CARMINE_DISP_WIDTH_SHIFT ; 
 int CARMINE_DISP_WIDTH_UNIT ; 
 int CARMINE_DISP_WIN_H_SHIFT ; 
 int CARMINE_EXTEND_MODE ; 
 int CARMINE_EXT_CMODE_DIRECT24_RGBA ; 
 int CARMINE_WINDOW_MODE ; 
 int /*<<< orphan*/  c_set_disp_reg (struct carmine_fb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void carmine_init_display_param(struct carmine_fb *par)
{
	u32 width;
	u32 height;
	u32 param;
	u32 window_size;
	u32 soffset = par->smem_offset;

	c_set_disp_reg(par, CARMINE_DISP_REG_C_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_MLMR_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_CURSOR_MODE,
			CARMINE_CURSOR0_PRIORITY_MASK |
			CARMINE_CURSOR1_PRIORITY_MASK |
			CARMINE_CURSOR_CUTZ_MASK);

	/* Set default cursor position */
	c_set_disp_reg(par, CARMINE_DISP_REG_CUR1_POS, 0 << 16 | 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_CUR2_POS, 0 << 16 | 0);

	/* Set default display mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_EXT_MODE, CARMINE_WINDOW_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_EXT_MODE,
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_EXT_MODE, CARMINE_EXTEND_MODE |
			CARMINE_EXT_CMODE_DIRECT24_RGBA);

	/* Set default frame size to layer mode register */
	width = par->res->hdp * 4 / CARMINE_DISP_WIDTH_UNIT;
	width = width << CARMINE_DISP_WIDTH_SHIFT;

	height = par->res->vdp - 1;
	param = width | height;

	c_set_disp_reg(par, CARMINE_DISP_REG_L0_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIDTH, width);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_MODE_W_H, param);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_MODE_W_H, param);

	/* Set default pos and size */
	window_size = (par->res->vdp - 1) << CARMINE_DISP_WIN_H_SHIFT;
	window_size |= par->res->hdp;

	c_set_disp_reg(par, CARMINE_DISP_REG_L0_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_WIN_SIZE, window_size);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_WIN_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_WIN_SIZE, window_size);

	/* Set default origin address */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_ORG_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_ORG_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_ORG_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_ORG_ADR1, soffset);

	/* Set default display address */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_DISP_ADR, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_DISP_ADR1, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_DISP_ADR0, soffset);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_DISP_ADR0, soffset);

	/* Set default display position */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_DISP_POS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_DISP_POS, 0);

	/* Set default blend mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L0, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L1, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L2, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L3, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L4, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L5, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L6, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_BLEND_MODE_L7, 0);

	/* default transparency mode */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L1_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6_TRANS, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7_TRANS, 0);

	/* Set default read skip parameter */
	c_set_disp_reg(par, CARMINE_DISP_REG_L0RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6RM, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7RM, 0);

	c_set_disp_reg(par, CARMINE_DISP_REG_L0PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6PX, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7PX, 0);

	c_set_disp_reg(par, CARMINE_DISP_REG_L0PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L2PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L3PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L4PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L5PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L6PY, 0);
	c_set_disp_reg(par, CARMINE_DISP_REG_L7PY, 0);
}