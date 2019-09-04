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
#define  MP_CSP_BT_601 130 
#define  MP_CSP_BT_709 129 
#define  MP_CSP_SMPTE_240M 128 
 int VA_SRC_BT601 ; 
 int VA_SRC_BT709 ; 
 int VA_SRC_SMPTE_240 ; 

int va_get_colorspace_flag(enum mp_csp csp)
{
    switch (csp) {
    case MP_CSP_BT_601:         return VA_SRC_BT601;
    case MP_CSP_BT_709:         return VA_SRC_BT709;
    case MP_CSP_SMPTE_240M:     return VA_SRC_SMPTE_240;
    }
    return 0;
}