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
typedef  int /*<<< orphan*/  zimg_color_primaries_e ;
typedef  enum mp_csp_prim { ____Placeholder_mp_csp_prim } mp_csp_prim ;

/* Variables and functions */
#define  MP_CSP_PRIM_ADOBE 140 
#define  MP_CSP_PRIM_APPLE 139 
#define  MP_CSP_PRIM_BT_2020 138 
#define  MP_CSP_PRIM_BT_470M 137 
#define  MP_CSP_PRIM_BT_601_525 136 
#define  MP_CSP_PRIM_BT_601_625 135 
#define  MP_CSP_PRIM_BT_709 134 
#define  MP_CSP_PRIM_CIE_1931 133 
#define  MP_CSP_PRIM_DCI_P3 132 
#define  MP_CSP_PRIM_DISPLAY_P3 131 
#define  MP_CSP_PRIM_PRO_PHOTO 130 
#define  MP_CSP_PRIM_S_GAMUT 129 
#define  MP_CSP_PRIM_V_GAMUT 128 
 int /*<<< orphan*/  ZIMG_PRIMARIES_BT2020 ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_BT470_BG ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_BT470_M ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_BT709 ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_ST170_M ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_ST428 ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_ST431_2 ; 
 int /*<<< orphan*/  ZIMG_PRIMARIES_ST432_1 ; 

__attribute__((used)) static zimg_color_primaries_e mp_to_z_prim(enum mp_csp_prim prim)
{
    switch (prim) {
    case MP_CSP_PRIM_BT_601_525:return ZIMG_PRIMARIES_ST170_M;
    case MP_CSP_PRIM_BT_601_625:return ZIMG_PRIMARIES_BT470_BG;
    case MP_CSP_PRIM_BT_709:    return ZIMG_PRIMARIES_BT709;
    case MP_CSP_PRIM_BT_2020:   return ZIMG_PRIMARIES_BT2020;
    case MP_CSP_PRIM_BT_470M:   return ZIMG_PRIMARIES_BT470_M;
    case MP_CSP_PRIM_CIE_1931:  return ZIMG_PRIMARIES_ST428;
    case MP_CSP_PRIM_DCI_P3:    return ZIMG_PRIMARIES_ST431_2;
    case MP_CSP_PRIM_DISPLAY_P3:return ZIMG_PRIMARIES_ST432_1;
    case MP_CSP_PRIM_APPLE:     // ?
    case MP_CSP_PRIM_ADOBE:
    case MP_CSP_PRIM_PRO_PHOTO:
    case MP_CSP_PRIM_V_GAMUT:
    case MP_CSP_PRIM_S_GAMUT:   // ?
    default:                    return ZIMG_PRIMARIES_BT709;
    }
}