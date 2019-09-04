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
 int AVCOL_SPC_BT2020_CL ; 
 int AVCOL_SPC_BT2020_NCL ; 
 int AVCOL_SPC_BT470BG ; 
 int AVCOL_SPC_BT709 ; 
 int AVCOL_SPC_RGB ; 
 int AVCOL_SPC_SMPTE240M ; 
 int AVCOL_SPC_UNSPECIFIED ; 
 int AVCOL_SPC_YCOCG ; 
#define  MP_CSP_BT_2020_C 134 
#define  MP_CSP_BT_2020_NC 133 
#define  MP_CSP_BT_601 132 
#define  MP_CSP_BT_709 131 
#define  MP_CSP_RGB 130 
#define  MP_CSP_SMPTE_240M 129 
#define  MP_CSP_YCGCO 128 

int mp_csp_to_avcol_spc(enum mp_csp colorspace)
{
    switch (colorspace) {
    case MP_CSP_BT_709:         return AVCOL_SPC_BT709;
    case MP_CSP_BT_601:         return AVCOL_SPC_BT470BG;
    case MP_CSP_BT_2020_NC:     return AVCOL_SPC_BT2020_NCL;
    case MP_CSP_BT_2020_C:      return AVCOL_SPC_BT2020_CL;
    case MP_CSP_SMPTE_240M:     return AVCOL_SPC_SMPTE240M;
    case MP_CSP_RGB:            return AVCOL_SPC_RGB;
    case MP_CSP_YCGCO:          return AVCOL_SPC_YCOCG;
    default:                    return AVCOL_SPC_UNSPECIFIED;
    }
}