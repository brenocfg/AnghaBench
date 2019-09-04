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
struct mmp_overlay {int dummy; } ;

/* Variables and functions */
#define  PIXFMT_BGR1555 144 
#define  PIXFMT_BGR565 143 
#define  PIXFMT_BGR888PACK 142 
#define  PIXFMT_BGR888UNPACK 141 
#define  PIXFMT_BGRA888 140 
#define  PIXFMT_RGB1555 139 
#define  PIXFMT_RGB565 138 
#define  PIXFMT_RGB888PACK 137 
#define  PIXFMT_RGB888UNPACK 136 
#define  PIXFMT_RGBA888 135 
#define  PIXFMT_UYVY 134 
#define  PIXFMT_VYUY 133 
#define  PIXFMT_YUV420P 132 
#define  PIXFMT_YUV422P 131 
#define  PIXFMT_YUYV 130 
#define  PIXFMT_YVU420P 129 
#define  PIXFMT_YVU422P 128 
 int dma_csc (int,int) ; 
 int dma_fmt (int,int) ; 
 int dma_palette (int /*<<< orphan*/ ) ; 
 int dma_swaprb (int,int) ; 
 int dma_swapuv (int,int) ; 
 int dma_swapyuv (int,int) ; 
 int overlay_is_vid (struct mmp_overlay*) ; 

__attribute__((used)) static u32 fmt_to_reg(struct mmp_overlay *overlay, int pix_fmt)
{
	u32 rbswap = 0, uvswap = 0, yuvswap = 0,
		csc_en = 0, val = 0,
		vid = overlay_is_vid(overlay);

	switch (pix_fmt) {
	case PIXFMT_RGB565:
	case PIXFMT_RGB1555:
	case PIXFMT_RGB888PACK:
	case PIXFMT_RGB888UNPACK:
	case PIXFMT_RGBA888:
		rbswap = 1;
		break;
	case PIXFMT_VYUY:
	case PIXFMT_YVU422P:
	case PIXFMT_YVU420P:
		uvswap = 1;
		break;
	case PIXFMT_YUYV:
		yuvswap = 1;
		break;
	default:
		break;
	}

	switch (pix_fmt) {
	case PIXFMT_RGB565:
	case PIXFMT_BGR565:
		break;
	case PIXFMT_RGB1555:
	case PIXFMT_BGR1555:
		val = 0x1;
		break;
	case PIXFMT_RGB888PACK:
	case PIXFMT_BGR888PACK:
		val = 0x2;
		break;
	case PIXFMT_RGB888UNPACK:
	case PIXFMT_BGR888UNPACK:
		val = 0x3;
		break;
	case PIXFMT_RGBA888:
	case PIXFMT_BGRA888:
		val = 0x4;
		break;
	case PIXFMT_UYVY:
	case PIXFMT_VYUY:
	case PIXFMT_YUYV:
		val = 0x5;
		csc_en = 1;
		break;
	case PIXFMT_YUV422P:
	case PIXFMT_YVU422P:
		val = 0x6;
		csc_en = 1;
		break;
	case PIXFMT_YUV420P:
	case PIXFMT_YVU420P:
		val = 0x7;
		csc_en = 1;
		break;
	default:
		break;
	}

	return (dma_palette(0) | dma_fmt(vid, val) |
		dma_swaprb(vid, rbswap) | dma_swapuv(vid, uvswap) |
		dma_swapyuv(vid, yuvswap) | dma_csc(vid, csc_en));
}