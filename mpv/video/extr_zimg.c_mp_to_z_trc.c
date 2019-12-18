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
typedef  int /*<<< orphan*/  zimg_transfer_characteristics_e ;
typedef  enum mp_csp_trc { ____Placeholder_mp_csp_trc } mp_csp_trc ;

/* Variables and functions */
#define  MP_CSP_TRC_BT_1886 142 
#define  MP_CSP_TRC_GAMMA18 141 
#define  MP_CSP_TRC_GAMMA20 140 
#define  MP_CSP_TRC_GAMMA22 139 
#define  MP_CSP_TRC_GAMMA24 138 
#define  MP_CSP_TRC_GAMMA26 137 
#define  MP_CSP_TRC_GAMMA28 136 
#define  MP_CSP_TRC_HLG 135 
#define  MP_CSP_TRC_LINEAR 134 
#define  MP_CSP_TRC_PQ 133 
#define  MP_CSP_TRC_PRO_PHOTO 132 
#define  MP_CSP_TRC_SRGB 131 
#define  MP_CSP_TRC_S_LOG1 130 
#define  MP_CSP_TRC_S_LOG2 129 
#define  MP_CSP_TRC_V_LOG 128 
 int /*<<< orphan*/  ZIMG_TRANSFER_ARIB_B67 ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_BT470_BG ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_BT470_M ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_BT709 ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_IEC_61966_2_1 ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_LINEAR ; 
 int /*<<< orphan*/  ZIMG_TRANSFER_ST2084 ; 

__attribute__((used)) static zimg_transfer_characteristics_e mp_to_z_trc(enum mp_csp_trc trc)
{
    switch (trc) {
    case MP_CSP_TRC_BT_1886:    return ZIMG_TRANSFER_BT709;
    case MP_CSP_TRC_SRGB:       return ZIMG_TRANSFER_IEC_61966_2_1;
    case MP_CSP_TRC_LINEAR:     return ZIMG_TRANSFER_LINEAR;
    case MP_CSP_TRC_GAMMA22:    return ZIMG_TRANSFER_BT470_M;
    case MP_CSP_TRC_GAMMA28:    return ZIMG_TRANSFER_BT470_BG;
    case MP_CSP_TRC_PQ:         return ZIMG_TRANSFER_ST2084;
    case MP_CSP_TRC_HLG:        return ZIMG_TRANSFER_ARIB_B67;
    case MP_CSP_TRC_GAMMA18:    // ?
    case MP_CSP_TRC_GAMMA20:
    case MP_CSP_TRC_GAMMA24:
    case MP_CSP_TRC_GAMMA26:
    case MP_CSP_TRC_PRO_PHOTO:
    case MP_CSP_TRC_V_LOG:
    case MP_CSP_TRC_S_LOG1:
    case MP_CSP_TRC_S_LOG2:     // ?
    default:                    return ZIMG_TRANSFER_BT709;
    }
}