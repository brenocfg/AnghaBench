#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dp_src2_source; int /*<<< orphan*/  dp_op; int /*<<< orphan*/  dp_rop3; int /*<<< orphan*/  dp_src_source; } ;
union dp_mix_u {int val; TYPE_3__ f; } ;
struct TYPE_8__ {int gmc_src_pitch_offset_cntl; int gmc_dst_pitch_offset_cntl; int gmc_src_clipping; int gmc_dst_clipping; int gmc_dst_datatype; int gmc_byte_pix_order; int gmc_clr_cmp_fcn_dis; int gmc_wr_msk_dis; int /*<<< orphan*/  gmc_dp_op; int /*<<< orphan*/  gmc_rop3; int /*<<< orphan*/  gmc_dp_src_source; int /*<<< orphan*/  gmc_src_datatype; int /*<<< orphan*/  gmc_brush_datatype; scalar_t__ gmc_default_sel; } ;
union dp_gui_master_cntl_u {int val; TYPE_4__ f; } ;
struct TYPE_6__ {int dp_dst_datatype; int dp_byte_pix_order; int /*<<< orphan*/  dp_src_datatype; int /*<<< orphan*/  dp_src2_datatype; scalar_t__ dp_src2_type; int /*<<< orphan*/  dp_brush_datatype; } ;
union dp_datatype_u {int val; TYPE_2__ f; } ;
struct TYPE_5__ {int dst_x_dir; int dst_y_dir; int src_x_dir; int src_y_dir; int dst_major_x; int src_major_x; } ;
union dp_cntl_u {int val; TYPE_1__ f; } ;
struct w100fb_par {int xres; int yres; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_OP_ROP ; 
 int /*<<< orphan*/  DP_SRC_MEM_RECTANGULAR ; 
 int /*<<< orphan*/  GMC_BRUSH_NONE ; 
 int /*<<< orphan*/  ROP3_SRCCOPY ; 
 int /*<<< orphan*/  SRC_DATATYPE_EQU_DST ; 
 int W100_FB_BASE ; 
 scalar_t__ mmDP_CNTL ; 
 scalar_t__ mmDP_DATATYPE ; 
 scalar_t__ mmDP_GUI_MASTER_CNTL ; 
 scalar_t__ mmDP_MIX ; 
 scalar_t__ mmDST_OFFSET ; 
 scalar_t__ mmDST_PITCH ; 
 scalar_t__ mmSC_BOTTOM_RIGHT ; 
 scalar_t__ mmSC_TOP_LEFT ; 
 scalar_t__ mmSRC_OFFSET ; 
 scalar_t__ mmSRC_PITCH ; 
 scalar_t__ mmSRC_SC_BOTTOM_RIGHT ; 
 scalar_t__ remapped_regs ; 
 int /*<<< orphan*/  w100_fifo_wait (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void w100_init_graphic_engine(struct w100fb_par *par)
{
	union dp_gui_master_cntl_u gmc;
	union dp_mix_u dp_mix;
	union dp_datatype_u dp_datatype;
	union dp_cntl_u dp_cntl;

	w100_fifo_wait(4);
	writel(W100_FB_BASE, remapped_regs + mmDST_OFFSET);
	writel(par->xres, remapped_regs + mmDST_PITCH);
	writel(W100_FB_BASE, remapped_regs + mmSRC_OFFSET);
	writel(par->xres, remapped_regs + mmSRC_PITCH);

	w100_fifo_wait(3);
	writel(0, remapped_regs + mmSC_TOP_LEFT);
	writel((par->yres << 16) | par->xres, remapped_regs + mmSC_BOTTOM_RIGHT);
	writel(0x1fff1fff, remapped_regs + mmSRC_SC_BOTTOM_RIGHT);

	w100_fifo_wait(4);
	dp_cntl.val = 0;
	dp_cntl.f.dst_x_dir = 1;
	dp_cntl.f.dst_y_dir = 1;
	dp_cntl.f.src_x_dir = 1;
	dp_cntl.f.src_y_dir = 1;
	dp_cntl.f.dst_major_x = 1;
	dp_cntl.f.src_major_x = 1;
	writel(dp_cntl.val, remapped_regs + mmDP_CNTL);

	gmc.val = 0;
	gmc.f.gmc_src_pitch_offset_cntl = 1;
	gmc.f.gmc_dst_pitch_offset_cntl = 1;
	gmc.f.gmc_src_clipping = 1;
	gmc.f.gmc_dst_clipping = 1;
	gmc.f.gmc_brush_datatype = GMC_BRUSH_NONE;
	gmc.f.gmc_dst_datatype = 3; /* from DstType_16Bpp_444 */
	gmc.f.gmc_src_datatype = SRC_DATATYPE_EQU_DST;
	gmc.f.gmc_byte_pix_order = 1;
	gmc.f.gmc_default_sel = 0;
	gmc.f.gmc_rop3 = ROP3_SRCCOPY;
	gmc.f.gmc_dp_src_source = DP_SRC_MEM_RECTANGULAR;
	gmc.f.gmc_clr_cmp_fcn_dis = 1;
	gmc.f.gmc_wr_msk_dis = 1;
	gmc.f.gmc_dp_op = DP_OP_ROP;
	writel(gmc.val, remapped_regs + mmDP_GUI_MASTER_CNTL);

	dp_datatype.val = dp_mix.val = 0;
	dp_datatype.f.dp_dst_datatype = gmc.f.gmc_dst_datatype;
	dp_datatype.f.dp_brush_datatype = gmc.f.gmc_brush_datatype;
	dp_datatype.f.dp_src2_type = 0;
	dp_datatype.f.dp_src2_datatype = gmc.f.gmc_src_datatype;
	dp_datatype.f.dp_src_datatype = gmc.f.gmc_src_datatype;
	dp_datatype.f.dp_byte_pix_order = gmc.f.gmc_byte_pix_order;
	writel(dp_datatype.val, remapped_regs + mmDP_DATATYPE);

	dp_mix.f.dp_src_source = gmc.f.gmc_dp_src_source;
	dp_mix.f.dp_src2_source = 1;
	dp_mix.f.dp_rop3 = gmc.f.gmc_rop3;
	dp_mix.f.dp_op = gmc.f.gmc_dp_op;
	writel(dp_mix.val, remapped_regs + mmDP_MIX);
}