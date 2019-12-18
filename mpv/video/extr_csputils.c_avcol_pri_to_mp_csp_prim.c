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
typedef  enum mp_csp_prim { ____Placeholder_mp_csp_prim } mp_csp_prim ;

/* Variables and functions */
#define  AVCOL_PRI_BT2020 133 
#define  AVCOL_PRI_BT470BG 132 
#define  AVCOL_PRI_BT470M 131 
#define  AVCOL_PRI_BT709 130 
#define  AVCOL_PRI_SMPTE170M 129 
#define  AVCOL_PRI_SMPTE240M 128 
 int MP_CSP_PRIM_AUTO ; 
 int MP_CSP_PRIM_BT_2020 ; 
 int MP_CSP_PRIM_BT_470M ; 
 int MP_CSP_PRIM_BT_601_525 ; 
 int MP_CSP_PRIM_BT_601_625 ; 
 int MP_CSP_PRIM_BT_709 ; 

enum mp_csp_prim avcol_pri_to_mp_csp_prim(int avpri)
{
    switch (avpri) {
    case AVCOL_PRI_SMPTE240M:   // Same as below
    case AVCOL_PRI_SMPTE170M:   return MP_CSP_PRIM_BT_601_525;
    case AVCOL_PRI_BT470BG:     return MP_CSP_PRIM_BT_601_625;
    case AVCOL_PRI_BT709:       return MP_CSP_PRIM_BT_709;
    case AVCOL_PRI_BT2020:      return MP_CSP_PRIM_BT_2020;
    case AVCOL_PRI_BT470M:      return MP_CSP_PRIM_BT_470M;
    default:                    return MP_CSP_PRIM_AUTO;
    }
}