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
typedef  enum mp_csp { ____Placeholder_mp_csp } mp_csp ;

/* Variables and functions */
#define  AVCOL_SPC_BT2020_CL 135 
#define  AVCOL_SPC_BT2020_NCL 134 
#define  AVCOL_SPC_BT470BG 133 
#define  AVCOL_SPC_BT709 132 
#define  AVCOL_SPC_RGB 131 
#define  AVCOL_SPC_SMPTE170M 130 
#define  AVCOL_SPC_SMPTE240M 129 
#define  AVCOL_SPC_YCOCG 128 
 int MP_CSP_AUTO ; 
 int MP_CSP_BT_2020_C ; 
 int MP_CSP_BT_2020_NC ; 
 int MP_CSP_BT_601 ; 
 int MP_CSP_BT_709 ; 
 int MP_CSP_RGB ; 
 int MP_CSP_SMPTE_240M ; 
 int MP_CSP_YCGCO ; 

enum mp_csp avcol_spc_to_mp_csp(int avcolorspace)
{
    switch (avcolorspace) {
    case AVCOL_SPC_BT709:       return MP_CSP_BT_709;
    case AVCOL_SPC_BT470BG:     return MP_CSP_BT_601;
    case AVCOL_SPC_BT2020_NCL:  return MP_CSP_BT_2020_NC;
    case AVCOL_SPC_BT2020_CL:   return MP_CSP_BT_2020_C;
    case AVCOL_SPC_SMPTE170M:   return MP_CSP_BT_601;
    case AVCOL_SPC_SMPTE240M:   return MP_CSP_SMPTE_240M;
    case AVCOL_SPC_RGB:         return MP_CSP_RGB;
    case AVCOL_SPC_YCOCG:       return MP_CSP_YCGCO;
    default:                    return MP_CSP_AUTO;
    }
}