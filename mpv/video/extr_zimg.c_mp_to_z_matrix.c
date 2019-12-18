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
typedef  int /*<<< orphan*/  zimg_matrix_coefficients_e ;
typedef  enum mp_csp { ____Placeholder_mp_csp } mp_csp ;

/* Variables and functions */
#define  MP_CSP_BT_2020_C 135 
#define  MP_CSP_BT_2020_NC 134 
#define  MP_CSP_BT_601 133 
#define  MP_CSP_BT_709 132 
#define  MP_CSP_RGB 131 
#define  MP_CSP_SMPTE_240M 130 
#define  MP_CSP_XYZ 129 
#define  MP_CSP_YCGCO 128 
 int /*<<< orphan*/  ZIMG_MATRIX_BT2020_CL ; 
 int /*<<< orphan*/  ZIMG_MATRIX_BT2020_NCL ; 
 int /*<<< orphan*/  ZIMG_MATRIX_BT470_BG ; 
 int /*<<< orphan*/  ZIMG_MATRIX_BT709 ; 
 int /*<<< orphan*/  ZIMG_MATRIX_RGB ; 
 int /*<<< orphan*/  ZIMG_MATRIX_ST240_M ; 
 int /*<<< orphan*/  ZIMG_MATRIX_YCGCO ; 

__attribute__((used)) static zimg_matrix_coefficients_e mp_to_z_matrix(enum mp_csp csp)
{
    switch (csp) {
    case MP_CSP_BT_601:         return ZIMG_MATRIX_BT470_BG;
    case MP_CSP_BT_709:         return ZIMG_MATRIX_BT709;
    case MP_CSP_SMPTE_240M:     return ZIMG_MATRIX_ST240_M;
    case MP_CSP_BT_2020_NC:     return ZIMG_MATRIX_BT2020_NCL;
    case MP_CSP_BT_2020_C:      return ZIMG_MATRIX_BT2020_CL;
    case MP_CSP_RGB:            return ZIMG_MATRIX_RGB;
    case MP_CSP_XYZ:            return ZIMG_MATRIX_RGB;
    case MP_CSP_YCGCO:          return ZIMG_MATRIX_YCGCO;
    default:                    return ZIMG_MATRIX_BT709;
    }
}