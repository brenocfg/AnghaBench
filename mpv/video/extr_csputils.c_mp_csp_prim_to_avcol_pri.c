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
 int AVCOL_PRI_BT2020 ; 
 int AVCOL_PRI_BT470BG ; 
 int AVCOL_PRI_BT470M ; 
 int AVCOL_PRI_BT709 ; 
 int AVCOL_PRI_SMPTE170M ; 
 int AVCOL_PRI_UNSPECIFIED ; 
#define  MP_CSP_PRIM_BT_2020 132 
#define  MP_CSP_PRIM_BT_470M 131 
#define  MP_CSP_PRIM_BT_601_525 130 
#define  MP_CSP_PRIM_BT_601_625 129 
#define  MP_CSP_PRIM_BT_709 128 

int mp_csp_prim_to_avcol_pri(enum mp_csp_prim prim)
{
    switch (prim) {
    case MP_CSP_PRIM_BT_601_525: return AVCOL_PRI_SMPTE170M;
    case MP_CSP_PRIM_BT_601_625: return AVCOL_PRI_BT470BG;
    case MP_CSP_PRIM_BT_709:     return AVCOL_PRI_BT709;
    case MP_CSP_PRIM_BT_2020:    return AVCOL_PRI_BT2020;
    case MP_CSP_PRIM_BT_470M:    return AVCOL_PRI_BT470M;
    default:                     return AVCOL_PRI_UNSPECIFIED;
    }
}