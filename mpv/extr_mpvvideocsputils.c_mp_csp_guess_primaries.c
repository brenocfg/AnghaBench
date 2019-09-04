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
typedef  enum mp_csp_prim { ____Placeholder_mp_csp_prim } mp_csp_prim ;

/* Variables and functions */
 int MP_CSP_PRIM_BT_601_525 ; 
 int MP_CSP_PRIM_BT_601_625 ; 
 int MP_CSP_PRIM_BT_709 ; 

enum mp_csp_prim mp_csp_guess_primaries(int width, int height)
{
    // HD content
    if (width >= 1280 || height > 576)
        return MP_CSP_PRIM_BT_709;

    switch (height) {
    case 576: // Typical PAL content, including anamorphic/squared
        return MP_CSP_PRIM_BT_601_625;

    case 480: // Typical NTSC content, including squared
    case 486: // NTSC Pro or anamorphic NTSC
        return MP_CSP_PRIM_BT_601_525;

    default: // No good metric, just pick BT.709 to minimize damage
        return MP_CSP_PRIM_BT_709;
    }
}