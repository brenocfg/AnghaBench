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
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;

/* Variables and functions */
#define  AVCOL_TRC_ARIB_STD_B67 139 
#define  AVCOL_TRC_BT1361_ECG 138 
#define  AVCOL_TRC_BT2020_10 137 
#define  AVCOL_TRC_BT2020_12 136 
#define  AVCOL_TRC_BT709 135 
#define  AVCOL_TRC_GAMMA22 134 
#define  AVCOL_TRC_GAMMA28 133 
#define  AVCOL_TRC_IEC61966_2_1 132 
#define  AVCOL_TRC_LINEAR 131 
#define  AVCOL_TRC_SMPTE170M 130 
#define  AVCOL_TRC_SMPTE240M 129 
#define  AVCOL_TRC_SMPTEST2084 128 
 int MP_CSP_TRC_AUTO ; 
 int MP_CSP_TRC_BT_1886 ; 
 int MP_CSP_TRC_GAMMA22 ; 
 int MP_CSP_TRC_GAMMA28 ; 
 int MP_CSP_TRC_HLG ; 
 int MP_CSP_TRC_LINEAR ; 
 int MP_CSP_TRC_PQ ; 
 int MP_CSP_TRC_SRGB ; 

enum mp_csp_trc avcol_trc_to_mp_csp_trc(int avtrc)
{
    switch (avtrc) {
    case AVCOL_TRC_BT709:
    case AVCOL_TRC_SMPTE170M:
    case AVCOL_TRC_SMPTE240M:
    case AVCOL_TRC_BT1361_ECG:
    case AVCOL_TRC_BT2020_10:
    case AVCOL_TRC_BT2020_12:    return MP_CSP_TRC_BT_1886;
    case AVCOL_TRC_IEC61966_2_1: return MP_CSP_TRC_SRGB;
    case AVCOL_TRC_LINEAR:       return MP_CSP_TRC_LINEAR;
    case AVCOL_TRC_GAMMA22:      return MP_CSP_TRC_GAMMA22;
    case AVCOL_TRC_GAMMA28:      return MP_CSP_TRC_GAMMA28;
    case AVCOL_TRC_SMPTEST2084:  return MP_CSP_TRC_PQ;
    case AVCOL_TRC_ARIB_STD_B67: return MP_CSP_TRC_HLG;
    default:                     return MP_CSP_TRC_AUTO;
    }
}