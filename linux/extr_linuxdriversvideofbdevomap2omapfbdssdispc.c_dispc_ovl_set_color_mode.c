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
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum omap_color_mode { ____Placeholder_omap_color_mode } omap_color_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
#define  OMAP_DSS_COLOR_ARGB16 146 
#define  OMAP_DSS_COLOR_ARGB16_1555 145 
#define  OMAP_DSS_COLOR_ARGB32 144 
#define  OMAP_DSS_COLOR_CLUT1 143 
#define  OMAP_DSS_COLOR_CLUT2 142 
#define  OMAP_DSS_COLOR_CLUT4 141 
#define  OMAP_DSS_COLOR_CLUT8 140 
#define  OMAP_DSS_COLOR_NV12 139 
#define  OMAP_DSS_COLOR_RGB12U 138 
#define  OMAP_DSS_COLOR_RGB16 137 
#define  OMAP_DSS_COLOR_RGB24P 136 
#define  OMAP_DSS_COLOR_RGB24U 135 
#define  OMAP_DSS_COLOR_RGBA16 134 
#define  OMAP_DSS_COLOR_RGBA32 133 
#define  OMAP_DSS_COLOR_RGBX16 132 
#define  OMAP_DSS_COLOR_RGBX32 131 
#define  OMAP_DSS_COLOR_UYVY 130 
#define  OMAP_DSS_COLOR_XRGB16_1555 129 
#define  OMAP_DSS_COLOR_YUV2 128 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dispc_ovl_set_color_mode(enum omap_plane plane,
		enum omap_color_mode color_mode)
{
	u32 m = 0;
	if (plane != OMAP_DSS_GFX) {
		switch (color_mode) {
		case OMAP_DSS_COLOR_NV12:
			m = 0x0; break;
		case OMAP_DSS_COLOR_RGBX16:
			m = 0x1; break;
		case OMAP_DSS_COLOR_RGBA16:
			m = 0x2; break;
		case OMAP_DSS_COLOR_RGB12U:
			m = 0x4; break;
		case OMAP_DSS_COLOR_ARGB16:
			m = 0x5; break;
		case OMAP_DSS_COLOR_RGB16:
			m = 0x6; break;
		case OMAP_DSS_COLOR_ARGB16_1555:
			m = 0x7; break;
		case OMAP_DSS_COLOR_RGB24U:
			m = 0x8; break;
		case OMAP_DSS_COLOR_RGB24P:
			m = 0x9; break;
		case OMAP_DSS_COLOR_YUV2:
			m = 0xa; break;
		case OMAP_DSS_COLOR_UYVY:
			m = 0xb; break;
		case OMAP_DSS_COLOR_ARGB32:
			m = 0xc; break;
		case OMAP_DSS_COLOR_RGBA32:
			m = 0xd; break;
		case OMAP_DSS_COLOR_RGBX32:
			m = 0xe; break;
		case OMAP_DSS_COLOR_XRGB16_1555:
			m = 0xf; break;
		default:
			BUG(); return;
		}
	} else {
		switch (color_mode) {
		case OMAP_DSS_COLOR_CLUT1:
			m = 0x0; break;
		case OMAP_DSS_COLOR_CLUT2:
			m = 0x1; break;
		case OMAP_DSS_COLOR_CLUT4:
			m = 0x2; break;
		case OMAP_DSS_COLOR_CLUT8:
			m = 0x3; break;
		case OMAP_DSS_COLOR_RGB12U:
			m = 0x4; break;
		case OMAP_DSS_COLOR_ARGB16:
			m = 0x5; break;
		case OMAP_DSS_COLOR_RGB16:
			m = 0x6; break;
		case OMAP_DSS_COLOR_ARGB16_1555:
			m = 0x7; break;
		case OMAP_DSS_COLOR_RGB24U:
			m = 0x8; break;
		case OMAP_DSS_COLOR_RGB24P:
			m = 0x9; break;
		case OMAP_DSS_COLOR_RGBX16:
			m = 0xa; break;
		case OMAP_DSS_COLOR_RGBA16:
			m = 0xb; break;
		case OMAP_DSS_COLOR_ARGB32:
			m = 0xc; break;
		case OMAP_DSS_COLOR_RGBA32:
			m = 0xd; break;
		case OMAP_DSS_COLOR_RGBX32:
			m = 0xe; break;
		case OMAP_DSS_COLOR_XRGB16_1555:
			m = 0xf; break;
		default:
			BUG(); return;
		}
	}

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), m, 4, 1);
}