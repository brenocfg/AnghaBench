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
typedef  int u32 ;
struct mbxfb_overlaySetup {int scaled_width; int scaled_height; int width; int height; int fmt; int Y_stride; int UV_stride; int U_offset; int V_offset; int mem_offset; scalar_t__ enable; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int EINVAL ; 
 int FMsk (int /*<<< orphan*/ ) ; 
#define  MBXFB_FMT_UY0VY1 133 
#define  MBXFB_FMT_VY0UY1 132 
#define  MBXFB_FMT_Y0UY1V 131 
#define  MBXFB_FMT_Y0VY1U 130 
#define  MBXFB_FMT_YUV12 129 
#define  MBXFB_FMT_YUV16 128 
 int /*<<< orphan*/  SHCTRL ; 
 int SHCTRL_HDECIM ; 
 int /*<<< orphan*/  SHCTRL_HPITCH ; 
 int /*<<< orphan*/  SPOCTRL ; 
 int SPOCTRL_HV_SC_OR ; 
 int SPOCTRL_H_SC_BP ; 
 int /*<<< orphan*/  SPOCTRL_VPITCH ; 
 int SPOCTRL_VS_UR_C ; 
 int SPOCTRL_V_SC_BP ; 
 int /*<<< orphan*/  SSSIZE ; 
 int /*<<< orphan*/  SSSIZE_SC_HEIGHT ; 
 int /*<<< orphan*/  SSSIZE_SC_WIDTH ; 
 int Shctrl_Hpitch (int) ; 
 int Spoctrl_Vpitch (int) ; 
 int Sssize_Sc_Height (int) ; 
 int Sssize_Sc_Width (int) ; 
 int /*<<< orphan*/  VOVRCLK ; 
 int /*<<< orphan*/  VSADR ; 
 int /*<<< orphan*/  VSCADR ; 
 int VSCADR_STR_EN ; 
 int /*<<< orphan*/  VSCADR_VBASE_ADR ; 
 int /*<<< orphan*/  VSCTRL ; 
 int VSCTRL_COSITED ; 
 int VSCTRL_CSC_EN ; 
 int VSCTRL_GAMMA_EN ; 
 int /*<<< orphan*/  VSCTRL_VPIXFMT ; 
 int VSCTRL_VPIXFMT_UY0VY1 ; 
 int VSCTRL_VPIXFMT_VY0UY1 ; 
 int VSCTRL_VPIXFMT_Y0UY1V ; 
 int VSCTRL_VPIXFMT_Y0VY1U ; 
 int VSCTRL_VPIXFMT_YUV12 ; 
 int /*<<< orphan*/  VSCTRL_VSHEIGHT ; 
 int /*<<< orphan*/  VSCTRL_VSWIDTH ; 
 int /*<<< orphan*/  VUBASE ; 
 int /*<<< orphan*/  VUBASE_UBASE_ADR ; 
 int VUBASE_UVHALFSTR ; 
 int /*<<< orphan*/  VVBASE ; 
 int /*<<< orphan*/  VVBASE_VBASE_ADR ; 
 int Vsadr_Srcstride (int) ; 
 int Vsadr_Xstart (int /*<<< orphan*/ ) ; 
 int Vsadr_Ystart (int /*<<< orphan*/ ) ; 
 int Vscadr_Vbase_Adr (int) ; 
 int Vsctrl_Height (int) ; 
 int Vsctrl_Width (int) ; 
 int Vubase_Ubase_Adr (int) ; 
 int Vvbase_Vbase_Adr (int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbxfb_setupOverlay(struct mbxfb_overlaySetup *set)
{
	u32 vsctrl, vscadr, vsadr;
	u32 sssize, spoctrl, shctrl;
	u32 vubase, vvbase;
	u32 vovrclk;

	if (set->scaled_width==0 || set->scaled_height==0)
		return -EINVAL;

	/* read registers which have reserved bits
	 * so we can write them back as-is. */
	vovrclk = readl(VOVRCLK);
	vsctrl = readl(VSCTRL);
	vscadr = readl(VSCADR);
	vubase = readl(VUBASE);
	vvbase = readl(VVBASE);
	shctrl = readl(SHCTRL);

	spoctrl = readl(SPOCTRL);
	sssize = readl(SSSIZE);

	vsctrl &= ~(	FMsk(VSCTRL_VSWIDTH) |
					FMsk(VSCTRL_VSHEIGHT) |
					FMsk(VSCTRL_VPIXFMT) |
					VSCTRL_GAMMA_EN | VSCTRL_CSC_EN |
					VSCTRL_COSITED );
	vsctrl |= Vsctrl_Width(set->width) | Vsctrl_Height(set->height) |
				VSCTRL_CSC_EN;

	vscadr &= ~(VSCADR_STR_EN | FMsk(VSCADR_VBASE_ADR) );
	vubase &= ~(VUBASE_UVHALFSTR | FMsk(VUBASE_UBASE_ADR));
	vvbase &= ~(FMsk(VVBASE_VBASE_ADR));

	switch (set->fmt) {
	case MBXFB_FMT_YUV16:
		vsctrl |= VSCTRL_VPIXFMT_YUV12;

		set->Y_stride = ((set->width) + 0xf ) & ~0xf;
		break;
	case MBXFB_FMT_YUV12:
		vsctrl |= VSCTRL_VPIXFMT_YUV12;

		set->Y_stride = ((set->width) + 0xf ) & ~0xf;
		vubase |= VUBASE_UVHALFSTR;

		break;
	case MBXFB_FMT_UY0VY1:
		vsctrl |= VSCTRL_VPIXFMT_UY0VY1;
		set->Y_stride = (set->width*2 + 0xf ) & ~0xf;
		break;
	case MBXFB_FMT_VY0UY1:
		vsctrl |= VSCTRL_VPIXFMT_VY0UY1;
		set->Y_stride = (set->width*2 + 0xf ) & ~0xf;
		break;
	case MBXFB_FMT_Y0UY1V:
		vsctrl |= VSCTRL_VPIXFMT_Y0UY1V;
		set->Y_stride = (set->width*2 + 0xf ) & ~0xf;
		break;
	case MBXFB_FMT_Y0VY1U:
		vsctrl |= VSCTRL_VPIXFMT_Y0VY1U;
		set->Y_stride = (set->width*2 + 0xf ) & ~0xf;
			break;
	default:
		return -EINVAL;
	}

	/* VSCTRL has the bits which sets the Video Pixel Format.
	 * When passing from a packed to planar format,
	 * if we write VSCTRL first, VVBASE and VUBASE would
	 * be zero if we would not set them here. (And then,
	 * the chips hangs and only a reset seems to fix it).
	 *
	 * If course, the values calculated here have no meaning
	 * for packed formats.
	 */
	set->UV_stride = ((set->width/2) + 0x7 ) & ~0x7;
		set->U_offset = set->height * set->Y_stride;
		set->V_offset = set->U_offset +
						set->height * set->UV_stride;
	vubase |= Vubase_Ubase_Adr(
			(0x60000 + set->mem_offset + set->U_offset)>>3);
	vvbase |= Vvbase_Vbase_Adr(
			(0x60000 + set->mem_offset + set->V_offset)>>3);


	vscadr |= Vscadr_Vbase_Adr((0x60000 + set->mem_offset)>>4);

	if (set->enable)
		vscadr |= VSCADR_STR_EN;


	vsadr = Vsadr_Srcstride((set->Y_stride)/16-1) |
		Vsadr_Xstart(set->x) | Vsadr_Ystart(set->y);

	sssize &= ~(FMsk(SSSIZE_SC_WIDTH) | FMsk(SSSIZE_SC_HEIGHT));
	sssize = Sssize_Sc_Width(set->scaled_width-1) |
			Sssize_Sc_Height(set->scaled_height-1);

	spoctrl &= ~(SPOCTRL_H_SC_BP | SPOCTRL_V_SC_BP |
			SPOCTRL_HV_SC_OR | SPOCTRL_VS_UR_C |
			FMsk(SPOCTRL_VPITCH));
	spoctrl |= Spoctrl_Vpitch((set->height<<11)/set->scaled_height);

	/* Bypass horiz/vert scaler when same size */
	if (set->scaled_width == set->width)
		spoctrl |= SPOCTRL_H_SC_BP;
	if (set->scaled_height == set->height)
		spoctrl |= SPOCTRL_V_SC_BP;

	shctrl &= ~(FMsk(SHCTRL_HPITCH) | SHCTRL_HDECIM);
	shctrl |= Shctrl_Hpitch((set->width<<11)/set->scaled_width);

	/* Video plane registers */
	write_reg(vsctrl, VSCTRL);
	write_reg(vscadr, VSCADR);
	write_reg(vubase, VUBASE);
	write_reg(vvbase, VVBASE);
	write_reg(vsadr, VSADR);

	/* Video scaler registers */
	write_reg(sssize, SSSIZE);
	write_reg(spoctrl, SPOCTRL);
	write_reg(shctrl, SHCTRL);

	/* Clock */
	if (set->enable)
		vovrclk |= 1;
	else
		vovrclk &= ~1;

	write_reg(vovrclk, VOVRCLK);

	return 0;
}