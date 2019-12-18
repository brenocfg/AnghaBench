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
 int MP_CSP_BT_601 ; 
 int MP_CSP_BT_709 ; 

enum mp_csp mp_csp_guess_colorspace(int width, int height)
{
    return width >= 1280 || height > 576 ? MP_CSP_BT_709 : MP_CSP_BT_601;
}