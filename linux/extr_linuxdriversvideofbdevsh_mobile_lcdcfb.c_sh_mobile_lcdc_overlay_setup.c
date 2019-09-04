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
struct sh_mobile_lcdc_overlay {int base_addr_y; int dma_handle; int base_addr_c; int xres_virtual; int yres_virtual; int mode; int alpha; int rop3; int yres; int xres; int pos_y; int pos_x; int pitch; int /*<<< orphan*/  index; TYPE_2__* channel; TYPE_1__* format; int /*<<< orphan*/  enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  lcdc; } ;
struct TYPE_3__ {int fourcc; } ;

/* Variables and functions */
#define  LCDC_OVERLAY_BLEND 138 
#define  LCDC_OVERLAY_ROP3 137 
 int LDBBLOCR_CHLC_SHIFT ; 
 int LDBBLOCR_CVLC_SHIFT ; 
 int LDBBSIFR_AL_1 ; 
 int LDBBSIFR_AL_PK ; 
 int LDBBSIFR_BRSEL ; 
 int LDBBSIFR_CHRR_420 ; 
 int LDBBSIFR_CHRR_422 ; 
 int LDBBSIFR_CHRR_444 ; 
 int LDBBSIFR_EN ; 
 int LDBBSIFR_LAY_SHIFT ; 
 int LDBBSIFR_ROP3_SHIFT ; 
 int LDBBSIFR_RPKF_RGB16 ; 
 int LDBBSIFR_RPKF_RGB24 ; 
 int LDBBSIFR_RY ; 
 int LDBBSIFR_SWPB ; 
 int LDBBSIFR_SWPL ; 
 int LDBBSIFR_SWPW ; 
 int LDBBSMWR_BSMW_SHIFT ; 
 int LDBBSSZR_BHSS_SHIFT ; 
 int LDBBSSZR_BVSS_SHIFT ; 
 int /*<<< orphan*/  LDBCR ; 
 int LDBCR_UPC (int /*<<< orphan*/ ) ; 
 int LDBCR_UPD (int /*<<< orphan*/ ) ; 
 int LDBCR_UPF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBLOCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSACR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSAYR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSIFR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSMWR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDBnBSSZR (int /*<<< orphan*/ ) ; 
 int LDDFR_PKF_ARGB32 ; 
#define  V4L2_PIX_FMT_BGR24 136 
#define  V4L2_PIX_FMT_BGR32 135 
#define  V4L2_PIX_FMT_NV12 134 
#define  V4L2_PIX_FMT_NV16 133 
#define  V4L2_PIX_FMT_NV21 132 
#define  V4L2_PIX_FMT_NV24 131 
#define  V4L2_PIX_FMT_NV42 130 
#define  V4L2_PIX_FMT_NV61 129 
#define  V4L2_PIX_FMT_RGB565 128 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lcdc_write_overlay (struct sh_mobile_lcdc_overlay*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_mobile_lcdc_overlay_setup(struct sh_mobile_lcdc_overlay *ovl)
{
	u32 format = 0;

	if (!ovl->enabled) {
		lcdc_write(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));
		lcdc_write_overlay(ovl, LDBnBSIFR(ovl->index), 0);
		lcdc_write(ovl->channel->lcdc, LDBCR,
			   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));
		return;
	}

	ovl->base_addr_y = ovl->dma_handle;
	ovl->base_addr_c = ovl->dma_handle
			 + ovl->xres_virtual * ovl->yres_virtual;

	switch (ovl->mode) {
	case LCDC_OVERLAY_BLEND:
		format = LDBBSIFR_EN | (ovl->alpha << LDBBSIFR_LAY_SHIFT);
		break;

	case LCDC_OVERLAY_ROP3:
		format = LDBBSIFR_EN | LDBBSIFR_BRSEL
		       | (ovl->rop3 << LDBBSIFR_ROP3_SHIFT);
		break;
	}

	switch (ovl->format->fourcc) {
	case V4L2_PIX_FMT_RGB565:
	case V4L2_PIX_FMT_NV21:
	case V4L2_PIX_FMT_NV61:
	case V4L2_PIX_FMT_NV42:
		format |= LDBBSIFR_SWPL | LDBBSIFR_SWPW;
		break;
	case V4L2_PIX_FMT_BGR24:
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV24:
		format |= LDBBSIFR_SWPL | LDBBSIFR_SWPW | LDBBSIFR_SWPB;
		break;
	case V4L2_PIX_FMT_BGR32:
	default:
		format |= LDBBSIFR_SWPL;
		break;
	}

	switch (ovl->format->fourcc) {
	case V4L2_PIX_FMT_RGB565:
		format |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB16;
		break;
	case V4L2_PIX_FMT_BGR24:
		format |= LDBBSIFR_AL_1 | LDBBSIFR_RY | LDBBSIFR_RPKF_RGB24;
		break;
	case V4L2_PIX_FMT_BGR32:
		format |= LDBBSIFR_AL_PK | LDBBSIFR_RY | LDDFR_PKF_ARGB32;
		break;
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		format |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_420;
		break;
	case V4L2_PIX_FMT_NV16:
	case V4L2_PIX_FMT_NV61:
		format |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_422;
		break;
	case V4L2_PIX_FMT_NV24:
	case V4L2_PIX_FMT_NV42:
		format |= LDBBSIFR_AL_1 | LDBBSIFR_CHRR_444;
		break;
	}

	lcdc_write(ovl->channel->lcdc, LDBCR, LDBCR_UPC(ovl->index));

	lcdc_write_overlay(ovl, LDBnBSIFR(ovl->index), format);

	lcdc_write_overlay(ovl, LDBnBSSZR(ovl->index),
		(ovl->yres << LDBBSSZR_BVSS_SHIFT) |
		(ovl->xres << LDBBSSZR_BHSS_SHIFT));
	lcdc_write_overlay(ovl, LDBnBLOCR(ovl->index),
		(ovl->pos_y << LDBBLOCR_CVLC_SHIFT) |
		(ovl->pos_x << LDBBLOCR_CHLC_SHIFT));
	lcdc_write_overlay(ovl, LDBnBSMWR(ovl->index),
		ovl->pitch << LDBBSMWR_BSMW_SHIFT);

	lcdc_write_overlay(ovl, LDBnBSAYR(ovl->index), ovl->base_addr_y);
	lcdc_write_overlay(ovl, LDBnBSACR(ovl->index), ovl->base_addr_c);

	lcdc_write(ovl->channel->lcdc, LDBCR,
		   LDBCR_UPF(ovl->index) | LDBCR_UPD(ovl->index));
}