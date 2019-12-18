#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dwCaps; } ;
struct TYPE_6__ {scalar_t__ dwCaps4; } ;
struct TYPE_7__ {TYPE_1__ u1; scalar_t__ dwCaps3; scalar_t__ dwCaps2; int /*<<< orphan*/  dwCaps; } ;
typedef  TYPE_2__ DDSCAPS2 ;
typedef  TYPE_3__ DDSCAPS ;

/* Variables and functions */

void DDRAW_Convert_DDSCAPS_1_To_2(const DDSCAPS* pIn, DDSCAPS2* pOut)
{
    /* 2 adds three additional caps fields to the end. Both versions
     * are unversioned. */
    pOut->dwCaps = pIn->dwCaps;
    pOut->dwCaps2 = 0;
    pOut->dwCaps3 = 0;
    pOut->u1.dwCaps4 = 0;
}