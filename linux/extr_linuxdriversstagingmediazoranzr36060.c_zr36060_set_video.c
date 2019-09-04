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
struct zr36060 {int width; int height; int total_code_vol; int real_code_vol; int max_block_vol; int /*<<< orphan*/  name; } ;
struct videocodec {scalar_t__ data; } ;
struct vfe_settings {int x; int y; int width; int height; int decimation; int quality; } ;
struct vfe_polarity {scalar_t__ vclk_pol; scalar_t__ pvalid_pol; scalar_t__ poe_pol; scalar_t__ subimg_pol; scalar_t__ blank_pol; scalar_t__ field_pol; int /*<<< orphan*/  hsync_pol; int /*<<< orphan*/  vsync_pol; } ;
struct tvnorm {int Ht; int Wt; int VStart; int Ha; int HStart; scalar_t__ Wa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZR060_AAR_HEND_HI ; 
 int /*<<< orphan*/  ZR060_AAR_HEND_LO ; 
 int /*<<< orphan*/  ZR060_AAR_HSTART_HI ; 
 int /*<<< orphan*/  ZR060_AAR_HSTART_LO ; 
 int /*<<< orphan*/  ZR060_AAR_VEND_HI ; 
 int /*<<< orphan*/  ZR060_AAR_VEND_LO ; 
 int /*<<< orphan*/  ZR060_AAR_VSTART_HI ; 
 int /*<<< orphan*/  ZR060_AAR_VSTART_LO ; 
 int /*<<< orphan*/  ZR060_BCR_U ; 
 int /*<<< orphan*/  ZR060_BCR_V ; 
 int /*<<< orphan*/  ZR060_BCR_Y ; 
 int /*<<< orphan*/  ZR060_LOAD ; 
 int ZR060_LOAD_SyncRst ; 
 int /*<<< orphan*/  ZR060_MBCVR ; 
 int /*<<< orphan*/  ZR060_SGR_BHEND_HI ; 
 int /*<<< orphan*/  ZR060_SGR_BHEND_LO ; 
 int /*<<< orphan*/  ZR060_SGR_BHSTART ; 
 int /*<<< orphan*/  ZR060_SGR_BVEND_HI ; 
 int /*<<< orphan*/  ZR060_SGR_BVEND_LO ; 
 int /*<<< orphan*/  ZR060_SGR_BVSTART ; 
 int /*<<< orphan*/  ZR060_SGR_HSYNC ; 
 int /*<<< orphan*/  ZR060_SGR_HTOTAL_HI ; 
 int /*<<< orphan*/  ZR060_SGR_HTOTAL_LO ; 
 int /*<<< orphan*/  ZR060_SGR_VSYNC ; 
 int /*<<< orphan*/  ZR060_SGR_VTOTAL_HI ; 
 int /*<<< orphan*/  ZR060_SGR_VTOTAL_LO ; 
 int /*<<< orphan*/  ZR060_SR ; 
 int ZR060_SR_HScale2 ; 
 int ZR060_SR_HScale4 ; 
 int ZR060_SR_VScale ; 
 int /*<<< orphan*/  ZR060_SWR_HEND_HI ; 
 int /*<<< orphan*/  ZR060_SWR_HEND_LO ; 
 int /*<<< orphan*/  ZR060_SWR_HSTART_HI ; 
 int /*<<< orphan*/  ZR060_SWR_HSTART_LO ; 
 int /*<<< orphan*/  ZR060_SWR_VEND_HI ; 
 int /*<<< orphan*/  ZR060_SWR_VEND_LO ; 
 int /*<<< orphan*/  ZR060_SWR_VSTART_HI ; 
 int /*<<< orphan*/  ZR060_SWR_VSTART_LO ; 
 int /*<<< orphan*/  ZR060_VPR ; 
 int ZR060_VPR_BLPol ; 
 int ZR060_VPR_FIPol ; 
 int ZR060_VPR_HSPol ; 
 int ZR060_VPR_PValPol ; 
 int ZR060_VPR_PoePol ; 
 int ZR060_VPR_SImgPol ; 
 int ZR060_VPR_VCLKPol ; 
 int ZR060_VPR_VSPol ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 scalar_t__ low_bitrate ; 
 int /*<<< orphan*/  zr36060_write (struct zr36060*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
zr36060_set_video (struct videocodec   *codec,
		   struct tvnorm       *norm,
		   struct vfe_settings *cap,
		   struct vfe_polarity *pol)
{
	struct zr36060 *ptr = (struct zr36060 *) codec->data;
	u32 reg;
	int size;

	dprintk(2, "%s: set_video %d/%d-%dx%d (%%%d) call\n", ptr->name,
		cap->x, cap->y, cap->width, cap->height, cap->decimation);

	/* if () return -EINVAL;
	 * trust the master driver that it knows what it does - so
	 * we allow invalid startx/y and norm for now ... */
	ptr->width = cap->width / (cap->decimation & 0xff);
	ptr->height = cap->height / (cap->decimation >> 8);

	zr36060_write(ptr, ZR060_LOAD, ZR060_LOAD_SyncRst);

	/* Note that VSPol/HSPol bits in zr36060 have the opposite
	 * meaning of their zr360x7 counterparts with the same names
	 * N.b. for VSPol this is only true if FIVEdge = 0 (default,
	 * left unchanged here - in accordance with datasheet).
	*/
	reg = (!pol->vsync_pol ? ZR060_VPR_VSPol : 0)
	    | (!pol->hsync_pol ? ZR060_VPR_HSPol : 0)
	    | (pol->field_pol ? ZR060_VPR_FIPol : 0)
	    | (pol->blank_pol ? ZR060_VPR_BLPol : 0)
	    | (pol->subimg_pol ? ZR060_VPR_SImgPol : 0)
	    | (pol->poe_pol ? ZR060_VPR_PoePol : 0)
	    | (pol->pvalid_pol ? ZR060_VPR_PValPol : 0)
	    | (pol->vclk_pol ? ZR060_VPR_VCLKPol : 0);
	zr36060_write(ptr, ZR060_VPR, reg);

	reg = 0;
	switch (cap->decimation & 0xff) {
	default:
	case 1:
		break;

	case 2:
		reg |= ZR060_SR_HScale2;
		break;

	case 4:
		reg |= ZR060_SR_HScale4;
		break;
	}

	switch (cap->decimation >> 8) {
	default:
	case 1:
		break;

	case 2:
		reg |= ZR060_SR_VScale;
		break;
	}
	zr36060_write(ptr, ZR060_SR, reg);

	zr36060_write(ptr, ZR060_BCR_Y, 0x00);
	zr36060_write(ptr, ZR060_BCR_U, 0x80);
	zr36060_write(ptr, ZR060_BCR_V, 0x80);

	/* sync generator */

	reg = norm->Ht - 1;	/* Vtotal */
	zr36060_write(ptr, ZR060_SGR_VTOTAL_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SGR_VTOTAL_LO, (reg >> 0) & 0xff);

	reg = norm->Wt - 1;	/* Htotal */
	zr36060_write(ptr, ZR060_SGR_HTOTAL_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SGR_HTOTAL_LO, (reg >> 0) & 0xff);

	reg = 6 - 1;		/* VsyncSize */
	zr36060_write(ptr, ZR060_SGR_VSYNC, reg);

	//reg   = 30 - 1;               /* HsyncSize */
///*CP*/        reg = (zr->params.norm == 1 ? 57 : 68);
	reg = 68;
	zr36060_write(ptr, ZR060_SGR_HSYNC, reg);

	reg = norm->VStart - 1;	/* BVstart */
	zr36060_write(ptr, ZR060_SGR_BVSTART, reg);

	reg += norm->Ha / 2;	/* BVend */
	zr36060_write(ptr, ZR060_SGR_BVEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SGR_BVEND_LO, (reg >> 0) & 0xff);

	reg = norm->HStart - 1;	/* BHstart */
	zr36060_write(ptr, ZR060_SGR_BHSTART, reg);

	reg += norm->Wa;	/* BHend */
	zr36060_write(ptr, ZR060_SGR_BHEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SGR_BHEND_LO, (reg >> 0) & 0xff);

	/* active area */
	reg = cap->y + norm->VStart;	/* Vstart */
	zr36060_write(ptr, ZR060_AAR_VSTART_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_AAR_VSTART_LO, (reg >> 0) & 0xff);

	reg += cap->height;	/* Vend */
	zr36060_write(ptr, ZR060_AAR_VEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_AAR_VEND_LO, (reg >> 0) & 0xff);

	reg = cap->x + norm->HStart;	/* Hstart */
	zr36060_write(ptr, ZR060_AAR_HSTART_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_AAR_HSTART_LO, (reg >> 0) & 0xff);

	reg += cap->width;	/* Hend */
	zr36060_write(ptr, ZR060_AAR_HEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_AAR_HEND_LO, (reg >> 0) & 0xff);

	/* subimage area */
	reg = norm->VStart - 4;	/* SVstart */
	zr36060_write(ptr, ZR060_SWR_VSTART_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SWR_VSTART_LO, (reg >> 0) & 0xff);

	reg += norm->Ha / 2 + 8;	/* SVend */
	zr36060_write(ptr, ZR060_SWR_VEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SWR_VEND_LO, (reg >> 0) & 0xff);

	reg = norm->HStart /*+ 64 */  - 4;	/* SHstart */
	zr36060_write(ptr, ZR060_SWR_HSTART_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SWR_HSTART_LO, (reg >> 0) & 0xff);

	reg += norm->Wa + 8;	/* SHend */
	zr36060_write(ptr, ZR060_SWR_HEND_HI, (reg >> 8) & 0xff);
	zr36060_write(ptr, ZR060_SWR_HEND_LO, (reg >> 0) & 0xff);

	size = ptr->width * ptr->height;
	/* Target compressed field size in bits: */
	size = size * 16;	/* uncompressed size in bits */
	/* (Ronald) by default, quality = 100 is a compression
	 * ratio 1:2. Setting low_bitrate (insmod option) sets
	 * it to 1:4 (instead of 1:2, zr36060 max) as limit because the
	 * buz can't handle more at decimation=1... Use low_bitrate if
	 * you have a Buz, unless you know what you're doing */
	size = size * cap->quality / (low_bitrate ? 400 : 200);
	/* Lower limit (arbitrary, 1 KB) */
	if (size < 8192)
		size = 8192;
	/* Upper limit: 7/8 of the code buffers */
	if (size > ptr->total_code_vol * 7)
		size = ptr->total_code_vol * 7;

	ptr->real_code_vol = size >> 3;	/* in bytes */

	/* the MBCVR is the *maximum* block volume, according to the
	 * JPEG ISO specs, this shouldn't be used, since that allows
	 * for the best encoding quality. So set it to it's max value */
	reg = ptr->max_block_vol;
	zr36060_write(ptr, ZR060_MBCVR, reg);

	return 0;
}