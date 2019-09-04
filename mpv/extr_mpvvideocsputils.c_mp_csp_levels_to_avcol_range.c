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
typedef  enum mp_csp_levels { ____Placeholder_mp_csp_levels } mp_csp_levels ;

/* Variables and functions */
 int AVCOL_RANGE_JPEG ; 
 int AVCOL_RANGE_MPEG ; 
 int AVCOL_RANGE_UNSPECIFIED ; 
#define  MP_CSP_LEVELS_PC 129 
#define  MP_CSP_LEVELS_TV 128 

int mp_csp_levels_to_avcol_range(enum mp_csp_levels range)
{
    switch (range) {
    case MP_CSP_LEVELS_TV:      return AVCOL_RANGE_MPEG;
    case MP_CSP_LEVELS_PC:      return AVCOL_RANGE_JPEG;
    default:                    return AVCOL_RANGE_UNSPECIFIED;
    }
}