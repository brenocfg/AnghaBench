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
 int mp_csp_to_avcol_spc (int) ; 

__attribute__((used)) static int mp_csp_to_sws_colorspace(enum mp_csp csp)
{
    // The SWS_CS_* macros are just convenience redefinitions of the
    // AVCOL_SPC_* macros, inside swscale.h.
    return mp_csp_to_avcol_spc(csp);
}