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
struct TYPE_2__ {int offset; } ;
struct intelfb_info {int pitch; TYPE_1__ fb; int /*<<< orphan*/  pll_index; } ;
struct intelfb_hwstate {int dpll_b; int fpb0; int fpb1; int hsync_b; int hblank_b; int htotal_b; int vsync_b; int vblank_b; int vtotal_b; int src_size_b; int pipe_b_conf; int dpll_a; int fpa0; int fpa1; int hsync_a; int hblank_a; int htotal_a; int vsync_a; int vblank_a; int vtotal_a; int src_size_a; int pipe_a_conf; int adpa; int disp_a_ctrl; int disp_a_stride; int disp_a_base; int /*<<< orphan*/  dvoc; int /*<<< orphan*/  dvob; int /*<<< orphan*/  vgacntrl; } ;
struct fb_var_screeninfo {int sync; int pixclock; int xres; int right_margin; int hsync_len; int left_margin; int yres; int vmode; int lower_margin; int vsync_len; int upper_margin; int yoffset; int xoffset; int bits_per_pixel; } ;

/* Variables and functions */
 int ADPA_DAC_ENABLE ; 
 int ADPA_DPMS_CONTROL_MASK ; 
 int ADPA_DPMS_D0 ; 
 int ADPA_HSYNC_ACTIVE_SHIFT ; 
 int ADPA_PIPE_SELECT_SHIFT ; 
 int ADPA_SYNC_ACTIVE_HIGH ; 
 int ADPA_SYNC_ACTIVE_LOW ; 
 int ADPA_SYNC_ACTIVE_MASK ; 
 int ADPA_USE_VGA_HVPOLARITY ; 
 int ADPA_VSYNC_ACTIVE_SHIFT ; 
 int /*<<< orphan*/  DBG_MSG (char*,...) ; 
 int DISPPLANE_15_16BPP ; 
 int DISPPLANE_16BPP ; 
 int DISPPLANE_32BPP_NO_ALPHA ; 
 int DISPPLANE_8BPP ; 
 int DISPPLANE_GAMMA_ENABLE ; 
 int DISPPLANE_PIXFORMAT_MASK ; 
 int DISPPLANE_PLANE_ENABLE ; 
 int DISPPLANE_SEL_PIPE_SHIFT ; 
 int DPLL_I9XX_P2_SHIFT ; 
 int DPLL_P1_FORCE_DIV2 ; 
 int DPLL_P1_MASK ; 
 int DPLL_P1_SHIFT ; 
 int DPLL_P2_MASK ; 
 int DPLL_P2_SHIFT ; 
 int DPLL_RATE_SELECT_FP0 ; 
 int DPLL_RATE_SELECT_MASK ; 
 int DPLL_REFERENCE_DEFAULT ; 
 int DPLL_REFERENCE_SELECT_MASK ; 
 int DPLL_VCO_ENABLE ; 
 int DPLL_VGA_MODE_DISABLE ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int FB_VMODE_INTERLACED ; 
 int FP_DIVISOR_MASK ; 
 int FP_M1_DIVISOR_SHIFT ; 
 int FP_M2_DIVISOR_SHIFT ; 
 int FP_N_DIVISOR_SHIFT ; 
 int HACTIVE_MASK ; 
 int HACTIVE_SHIFT ; 
 int HBLANKEND_MASK ; 
 int HBLANKSTART_MASK ; 
 int HBLANKSTART_SHIFT ; 
 int HSYNCEND_MASK ; 
 int HSYNCEND_SHIFT ; 
 int HSYNCSTART_MASK ; 
 int HSYNCSTART_SHIFT ; 
 int HTOTAL_MASK ; 
 int HTOTAL_SHIFT ; 
 scalar_t__ IS_I9XX (struct intelfb_info*) ; 
 int PIPECONF_GAMMA ; 
 int PIPECONF_INTERLACE_MASK ; 
 int PIPECONF_INTERLACE_W_FIELD_INDICATION ; 
 int PIPE_B ; 
 int PIPE_MASK ; 
 int /*<<< orphan*/  PORT_ENABLE ; 
 int SRC_SIZE_HORIZ_SHIFT ; 
 int SRC_SIZE_VERT_SHIFT ; 
 int STRIDE_ALIGNMENT ; 
 int STRIDE_ALIGNMENT_I9XX ; 
 int VACTIVE_MASK ; 
 int VACTIVE_SHIFT ; 
 int VBLANKEND_MASK ; 
 int VBLANKSTART_MASK ; 
 int VBLANKSTART_SHIFT ; 
 int /*<<< orphan*/  VGA_DISABLE ; 
 int VSYNCEND_MASK ; 
 int VSYNCEND_SHIFT ; 
 int VSYNCSTART_MASK ; 
 int VSYNCSTART_SHIFT ; 
 int VTOTAL_MASK ; 
 int VTOTAL_SHIFT ; 
 int /*<<< orphan*/  WRN_MSG (char*,...) ; 
 scalar_t__ calc_pll_params (int /*<<< orphan*/ ,int,int*,int*,int*,int*,int*,int*) ; 
 scalar_t__ check_overflow (int,int,char*) ; 
 int intelfb_var_to_depth (struct fb_var_screeninfo*) ; 
 int intelfbhw_active_pipe (struct intelfb_hwstate*) ; 

int intelfbhw_mode_to_hw(struct intelfb_info *dinfo,
			 struct intelfb_hwstate *hw,
			 struct fb_var_screeninfo *var)
{
	int pipe = intelfbhw_active_pipe(hw);
	u32 *dpll, *fp0, *fp1;
	u32 m1, m2, n, p1, p2, clock_target, clock;
	u32 hsync_start, hsync_end, hblank_start, hblank_end, htotal, hactive;
	u32 vsync_start, vsync_end, vblank_start, vblank_end, vtotal, vactive;
	u32 vsync_pol, hsync_pol;
	u32 *vs, *vb, *vt, *hs, *hb, *ht, *ss, *pipe_conf;
	u32 stride_alignment;

	DBG_MSG("intelfbhw_mode_to_hw\n");

	/* Disable VGA */
	hw->vgacntrl |= VGA_DISABLE;

	/* Set which pipe's registers will be set. */
	if (pipe == PIPE_B) {
		dpll = &hw->dpll_b;
		fp0 = &hw->fpb0;
		fp1 = &hw->fpb1;
		hs = &hw->hsync_b;
		hb = &hw->hblank_b;
		ht = &hw->htotal_b;
		vs = &hw->vsync_b;
		vb = &hw->vblank_b;
		vt = &hw->vtotal_b;
		ss = &hw->src_size_b;
		pipe_conf = &hw->pipe_b_conf;
	} else {
		dpll = &hw->dpll_a;
		fp0 = &hw->fpa0;
		fp1 = &hw->fpa1;
		hs = &hw->hsync_a;
		hb = &hw->hblank_a;
		ht = &hw->htotal_a;
		vs = &hw->vsync_a;
		vb = &hw->vblank_a;
		vt = &hw->vtotal_a;
		ss = &hw->src_size_a;
		pipe_conf = &hw->pipe_a_conf;
	}

	/* Use ADPA register for sync control. */
	hw->adpa &= ~ADPA_USE_VGA_HVPOLARITY;

	/* sync polarity */
	hsync_pol = (var->sync & FB_SYNC_HOR_HIGH_ACT) ?
			ADPA_SYNC_ACTIVE_HIGH : ADPA_SYNC_ACTIVE_LOW;
	vsync_pol = (var->sync & FB_SYNC_VERT_HIGH_ACT) ?
			ADPA_SYNC_ACTIVE_HIGH : ADPA_SYNC_ACTIVE_LOW;
	hw->adpa &= ~((ADPA_SYNC_ACTIVE_MASK << ADPA_VSYNC_ACTIVE_SHIFT) |
		      (ADPA_SYNC_ACTIVE_MASK << ADPA_HSYNC_ACTIVE_SHIFT));
	hw->adpa |= (hsync_pol << ADPA_HSYNC_ACTIVE_SHIFT) |
		    (vsync_pol << ADPA_VSYNC_ACTIVE_SHIFT);

	/* Connect correct pipe to the analog port DAC */
	hw->adpa &= ~(PIPE_MASK << ADPA_PIPE_SELECT_SHIFT);
	hw->adpa |= (pipe << ADPA_PIPE_SELECT_SHIFT);

	/* Set DPMS state to D0 (on) */
	hw->adpa &= ~ADPA_DPMS_CONTROL_MASK;
	hw->adpa |= ADPA_DPMS_D0;

	hw->adpa |= ADPA_DAC_ENABLE;

	*dpll |= (DPLL_VCO_ENABLE | DPLL_VGA_MODE_DISABLE);
	*dpll &= ~(DPLL_RATE_SELECT_MASK | DPLL_REFERENCE_SELECT_MASK);
	*dpll |= (DPLL_REFERENCE_DEFAULT | DPLL_RATE_SELECT_FP0);

	/* Desired clock in kHz */
	clock_target = 1000000000 / var->pixclock;

	if (calc_pll_params(dinfo->pll_index, clock_target, &m1, &m2,
			    &n, &p1, &p2, &clock)) {
		WRN_MSG("calc_pll_params failed\n");
		return 1;
	}

	/* Check for overflow. */
	if (check_overflow(p1, DPLL_P1_MASK, "PLL P1 parameter"))
		return 1;
	if (check_overflow(p2, DPLL_P2_MASK, "PLL P2 parameter"))
		return 1;
	if (check_overflow(m1, FP_DIVISOR_MASK, "PLL M1 parameter"))
		return 1;
	if (check_overflow(m2, FP_DIVISOR_MASK, "PLL M2 parameter"))
		return 1;
	if (check_overflow(n, FP_DIVISOR_MASK, "PLL N parameter"))
		return 1;

	*dpll &= ~DPLL_P1_FORCE_DIV2;
	*dpll &= ~((DPLL_P2_MASK << DPLL_P2_SHIFT) |
		   (DPLL_P1_MASK << DPLL_P1_SHIFT));

	if (IS_I9XX(dinfo)) {
		*dpll |= (p2 << DPLL_I9XX_P2_SHIFT);
		*dpll |= (1 << (p1 - 1)) << DPLL_P1_SHIFT;
	} else
		*dpll |= (p2 << DPLL_P2_SHIFT) | (p1 << DPLL_P1_SHIFT);

	*fp0 = (n << FP_N_DIVISOR_SHIFT) |
	       (m1 << FP_M1_DIVISOR_SHIFT) |
	       (m2 << FP_M2_DIVISOR_SHIFT);
	*fp1 = *fp0;

	hw->dvob &= ~PORT_ENABLE;
	hw->dvoc &= ~PORT_ENABLE;

	/* Use display plane A. */
	hw->disp_a_ctrl |= DISPPLANE_PLANE_ENABLE;
	hw->disp_a_ctrl &= ~DISPPLANE_GAMMA_ENABLE;
	hw->disp_a_ctrl &= ~DISPPLANE_PIXFORMAT_MASK;
	switch (intelfb_var_to_depth(var)) {
	case 8:
		hw->disp_a_ctrl |= DISPPLANE_8BPP | DISPPLANE_GAMMA_ENABLE;
		break;
	case 15:
		hw->disp_a_ctrl |= DISPPLANE_15_16BPP;
		break;
	case 16:
		hw->disp_a_ctrl |= DISPPLANE_16BPP;
		break;
	case 24:
		hw->disp_a_ctrl |= DISPPLANE_32BPP_NO_ALPHA;
		break;
	}
	hw->disp_a_ctrl &= ~(PIPE_MASK << DISPPLANE_SEL_PIPE_SHIFT);
	hw->disp_a_ctrl |= (pipe << DISPPLANE_SEL_PIPE_SHIFT);

	/* Set CRTC registers. */
	hactive = var->xres;
	hsync_start = hactive + var->right_margin;
	hsync_end = hsync_start + var->hsync_len;
	htotal = hsync_end + var->left_margin;
	hblank_start = hactive;
	hblank_end = htotal;

	DBG_MSG("H: act %d, ss %d, se %d, tot %d bs %d, be %d\n",
		hactive, hsync_start, hsync_end, htotal, hblank_start,
		hblank_end);

	vactive = var->yres;
	if (var->vmode & FB_VMODE_INTERLACED)
		vactive--; /* the chip adds 2 halflines automatically */
	vsync_start = vactive + var->lower_margin;
	vsync_end = vsync_start + var->vsync_len;
	vtotal = vsync_end + var->upper_margin;
	vblank_start = vactive;
	vblank_end = vsync_end + 1;

	DBG_MSG("V: act %d, ss %d, se %d, tot %d bs %d, be %d\n",
		vactive, vsync_start, vsync_end, vtotal, vblank_start,
		vblank_end);

	/* Adjust for register values, and check for overflow. */
	hactive--;
	if (check_overflow(hactive, HACTIVE_MASK, "CRTC hactive"))
		return 1;
	hsync_start--;
	if (check_overflow(hsync_start, HSYNCSTART_MASK, "CRTC hsync_start"))
		return 1;
	hsync_end--;
	if (check_overflow(hsync_end, HSYNCEND_MASK, "CRTC hsync_end"))
		return 1;
	htotal--;
	if (check_overflow(htotal, HTOTAL_MASK, "CRTC htotal"))
		return 1;
	hblank_start--;
	if (check_overflow(hblank_start, HBLANKSTART_MASK, "CRTC hblank_start"))
		return 1;
	hblank_end--;
	if (check_overflow(hblank_end, HBLANKEND_MASK, "CRTC hblank_end"))
		return 1;

	vactive--;
	if (check_overflow(vactive, VACTIVE_MASK, "CRTC vactive"))
		return 1;
	vsync_start--;
	if (check_overflow(vsync_start, VSYNCSTART_MASK, "CRTC vsync_start"))
		return 1;
	vsync_end--;
	if (check_overflow(vsync_end, VSYNCEND_MASK, "CRTC vsync_end"))
		return 1;
	vtotal--;
	if (check_overflow(vtotal, VTOTAL_MASK, "CRTC vtotal"))
		return 1;
	vblank_start--;
	if (check_overflow(vblank_start, VBLANKSTART_MASK, "CRTC vblank_start"))
		return 1;
	vblank_end--;
	if (check_overflow(vblank_end, VBLANKEND_MASK, "CRTC vblank_end"))
		return 1;

	*ht = (htotal << HTOTAL_SHIFT) | (hactive << HACTIVE_SHIFT);
	*hb = (hblank_start << HBLANKSTART_SHIFT) |
	      (hblank_end << HSYNCEND_SHIFT);
	*hs = (hsync_start << HSYNCSTART_SHIFT) | (hsync_end << HSYNCEND_SHIFT);

	*vt = (vtotal << VTOTAL_SHIFT) | (vactive << VACTIVE_SHIFT);
	*vb = (vblank_start << VBLANKSTART_SHIFT) |
	      (vblank_end << VSYNCEND_SHIFT);
	*vs = (vsync_start << VSYNCSTART_SHIFT) | (vsync_end << VSYNCEND_SHIFT);
	*ss = (hactive << SRC_SIZE_HORIZ_SHIFT) |
	      (vactive << SRC_SIZE_VERT_SHIFT);

	hw->disp_a_stride = dinfo->pitch;
	DBG_MSG("pitch is %d\n", hw->disp_a_stride);

	hw->disp_a_base = hw->disp_a_stride * var->yoffset +
			  var->xoffset * var->bits_per_pixel / 8;

	hw->disp_a_base += dinfo->fb.offset << 12;

	/* Check stride alignment. */
	stride_alignment = IS_I9XX(dinfo) ? STRIDE_ALIGNMENT_I9XX :
					    STRIDE_ALIGNMENT;
	if (hw->disp_a_stride % stride_alignment != 0) {
		WRN_MSG("display stride %d has bad alignment %d\n",
			hw->disp_a_stride, stride_alignment);
		return 1;
	}

	/* Set the palette to 8-bit mode. */
	*pipe_conf &= ~PIPECONF_GAMMA;

	if (var->vmode & FB_VMODE_INTERLACED)
		*pipe_conf |= PIPECONF_INTERLACE_W_FIELD_INDICATION;
	else
		*pipe_conf &= ~PIPECONF_INTERLACE_MASK;

	return 0;
}