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
struct crtc {int gen_cntl; int h_tot_disp; int v_tot_disp; int h_sync_strt_wid; int v_sync_strt_wid; int off_pitch; int vline_crnt_vline; } ;
struct atyfb_par {int dummy; } ;

/* Variables and functions */
 int CRTC_CSYNC_EN ; 
 int CRTC_EN ; 
 int /*<<< orphan*/  CRTC_GEN_CNTL ; 
 int /*<<< orphan*/  CRTC_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_H_TOTAL_DISP ; 
 int /*<<< orphan*/  CRTC_OFF_PITCH ; 
 int /*<<< orphan*/  CRTC_VLINE_CRNT_VLINE ; 
 int /*<<< orphan*/  CRTC_V_SYNC_STRT_WID ; 
 int /*<<< orphan*/  CRTC_V_TOTAL_DISP ; 
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int,struct atyfb_par const*) ; 

__attribute__((used)) static void aty_set_crtc(const struct atyfb_par *par, const struct crtc *crtc)
{
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	if (par->lcd_table != 0) {
		/* stop CRTC */
		aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl &
			    ~(CRTC_EXT_DISP_EN | CRTC_EN), par);

		/* update non-shadow registers first */
		aty_st_lcd(CNFG_PANEL, crtc->lcd_config_panel, par);
		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl &
			   ~(CRTC_RW_SELECT | SHADOW_EN | SHADOW_RW_EN), par);

		/* temporarily disable stretching */
		aty_st_lcd(HORZ_STRETCHING, crtc->horz_stretching &
			   ~(HORZ_STRETCH_MODE | HORZ_STRETCH_EN), par);
		aty_st_lcd(VERT_STRETCHING, crtc->vert_stretching &
			   ~(VERT_STRETCH_RATIO1 | VERT_STRETCH_RATIO2 |
			     VERT_STRETCH_USE0 | VERT_STRETCH_EN), par);
	}
#endif
	/* turn off CRT */
	aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl & ~CRTC_EN, par);

	DPRINTK("setting up CRTC\n");
	DPRINTK("set primary CRT to %ix%i %c%c composite %c\n",
		((((crtc->h_tot_disp >> 16) & 0xff) + 1) << 3),
		(((crtc->v_tot_disp >> 16) & 0x7ff) + 1),
		(crtc->h_sync_strt_wid & 0x200000) ? 'N' : 'P',
		(crtc->v_sync_strt_wid & 0x200000) ? 'N' : 'P',
		(crtc->gen_cntl & CRTC_CSYNC_EN) ? 'P' : 'N');

	DPRINTK("CRTC_H_TOTAL_DISP: %x\n", crtc->h_tot_disp);
	DPRINTK("CRTC_H_SYNC_STRT_WID: %x\n", crtc->h_sync_strt_wid);
	DPRINTK("CRTC_V_TOTAL_DISP: %x\n", crtc->v_tot_disp);
	DPRINTK("CRTC_V_SYNC_STRT_WID: %x\n", crtc->v_sync_strt_wid);
	DPRINTK("CRTC_OFF_PITCH: %x\n", crtc->off_pitch);
	DPRINTK("CRTC_VLINE_CRNT_VLINE: %x\n", crtc->vline_crnt_vline);
	DPRINTK("CRTC_GEN_CNTL: %x\n", crtc->gen_cntl);

	aty_st_le32(CRTC_H_TOTAL_DISP, crtc->h_tot_disp, par);
	aty_st_le32(CRTC_H_SYNC_STRT_WID, crtc->h_sync_strt_wid, par);
	aty_st_le32(CRTC_V_TOTAL_DISP, crtc->v_tot_disp, par);
	aty_st_le32(CRTC_V_SYNC_STRT_WID, crtc->v_sync_strt_wid, par);
	aty_st_le32(CRTC_OFF_PITCH, crtc->off_pitch, par);
	aty_st_le32(CRTC_VLINE_CRNT_VLINE, crtc->vline_crnt_vline, par);

	aty_st_le32(CRTC_GEN_CNTL, crtc->gen_cntl, par);
#if 0
	FIXME
	if (par->accel_flags & FB_ACCELF_TEXT)
		aty_init_engine(par, info);
#endif
#ifdef CONFIG_FB_ATY_GENERIC_LCD
	/* after setting the CRTC registers we should set the LCD registers. */
	if (par->lcd_table != 0) {
		/* switch to shadow registers */
		aty_st_lcd(LCD_GEN_CNTL, (crtc->lcd_gen_cntl & ~CRTC_RW_SELECT) |
			   SHADOW_EN | SHADOW_RW_EN, par);

		DPRINTK("set shadow CRT to %ix%i %c%c\n",
			((((crtc->shadow_h_tot_disp >> 16) & 0xff) + 1) << 3),
			(((crtc->shadow_v_tot_disp >> 16) & 0x7ff) + 1),
			(crtc->shadow_h_sync_strt_wid & 0x200000) ? 'N' : 'P',
			(crtc->shadow_v_sync_strt_wid & 0x200000) ? 'N' : 'P');

		DPRINTK("SHADOW CRTC_H_TOTAL_DISP: %x\n",
			crtc->shadow_h_tot_disp);
		DPRINTK("SHADOW CRTC_H_SYNC_STRT_WID: %x\n",
			crtc->shadow_h_sync_strt_wid);
		DPRINTK("SHADOW CRTC_V_TOTAL_DISP: %x\n",
			crtc->shadow_v_tot_disp);
		DPRINTK("SHADOW CRTC_V_SYNC_STRT_WID: %x\n",
			crtc->shadow_v_sync_strt_wid);

		aty_st_le32(CRTC_H_TOTAL_DISP, crtc->shadow_h_tot_disp, par);
		aty_st_le32(CRTC_H_SYNC_STRT_WID, crtc->shadow_h_sync_strt_wid, par);
		aty_st_le32(CRTC_V_TOTAL_DISP, crtc->shadow_v_tot_disp, par);
		aty_st_le32(CRTC_V_SYNC_STRT_WID, crtc->shadow_v_sync_strt_wid, par);

		/* restore CRTC selection & shadow state and enable stretching */
		DPRINTK("LCD_GEN_CNTL: %x\n", crtc->lcd_gen_cntl);
		DPRINTK("HORZ_STRETCHING: %x\n", crtc->horz_stretching);
		DPRINTK("VERT_STRETCHING: %x\n", crtc->vert_stretching);
		if (!M64_HAS(LT_LCD_REGS))
			DPRINTK("EXT_VERT_STRETCH: %x\n", crtc->ext_vert_stretch);

		aty_st_lcd(LCD_GEN_CNTL, crtc->lcd_gen_cntl, par);
		aty_st_lcd(HORZ_STRETCHING, crtc->horz_stretching, par);
		aty_st_lcd(VERT_STRETCHING, crtc->vert_stretching, par);
		if (!M64_HAS(LT_LCD_REGS)) {
			aty_st_lcd(EXT_VERT_STRETCH, crtc->ext_vert_stretch, par);
			aty_ld_le32(LCD_INDEX, par);
			aty_st_le32(LCD_INDEX, crtc->lcd_index, par);
		}
	}
#endif /* CONFIG_FB_ATY_GENERIC_LCD */
}