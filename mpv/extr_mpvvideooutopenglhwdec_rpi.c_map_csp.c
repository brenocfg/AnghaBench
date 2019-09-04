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
typedef  int /*<<< orphan*/  MMAL_FOURCC_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_COLOR_SPACE_ITUR_BT601 ; 
 int /*<<< orphan*/  MMAL_COLOR_SPACE_ITUR_BT709 ; 
 int /*<<< orphan*/  MMAL_COLOR_SPACE_SMPTE240M ; 
 int /*<<< orphan*/  MMAL_COLOR_SPACE_UNKNOWN ; 
#define  MP_CSP_BT_601 130 
#define  MP_CSP_BT_709 129 
#define  MP_CSP_SMPTE_240M 128 

__attribute__((used)) static MMAL_FOURCC_T map_csp(enum mp_csp csp)
{
    switch (csp) {
    case MP_CSP_BT_601:     return MMAL_COLOR_SPACE_ITUR_BT601;
    case MP_CSP_BT_709:     return MMAL_COLOR_SPACE_ITUR_BT709;
    case MP_CSP_SMPTE_240M: return MMAL_COLOR_SPACE_SMPTE240M;
    default:                return MMAL_COLOR_SPACE_UNKNOWN;
    }
}