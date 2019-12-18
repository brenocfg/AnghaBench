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
#define  AVCOL_RANGE_JPEG 129 
#define  AVCOL_RANGE_MPEG 128 
 int MP_CSP_LEVELS_AUTO ; 
 int MP_CSP_LEVELS_PC ; 
 int MP_CSP_LEVELS_TV ; 

enum mp_csp_levels avcol_range_to_mp_csp_levels(int avrange)
{
    switch (avrange) {
    case AVCOL_RANGE_MPEG:      return MP_CSP_LEVELS_TV;
    case AVCOL_RANGE_JPEG:      return MP_CSP_LEVELS_PC;
    default:                    return MP_CSP_LEVELS_AUTO;
    }
}