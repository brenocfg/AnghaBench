#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float x; float y; } ;
struct TYPE_7__ {float value; float fract; } ;
struct TYPE_8__ {float value; float fract; } ;
struct TYPE_9__ {TYPE_1__ y; TYPE_2__ x; } ;
typedef  TYPE_3__ POINTFX ;
typedef  TYPE_4__ D3DXVECTOR2 ;

/* Variables and functions */

__attribute__((used)) static inline D3DXVECTOR2 *convert_fixed_to_float(POINTFX *pt, int count, unsigned int emsquare)
{
    D3DXVECTOR2 *ret = (D3DXVECTOR2*)pt;
    while (count--) {
        D3DXVECTOR2 *pt_flt = (D3DXVECTOR2*)pt;
        pt_flt->x = (pt->x.value + pt->x.fract / (float)0x10000) / emsquare;
        pt_flt->y = (pt->y.value + pt->y.fract / (float)0x10000) / emsquare;
        pt++;
    }
    return ret;
}