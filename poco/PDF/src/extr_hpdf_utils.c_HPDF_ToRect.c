#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* top; void* right; void* bottom; void* left; } ;
typedef  TYPE_1__ HPDF_Rect ;
typedef  void* HPDF_REAL ;

/* Variables and functions */

HPDF_Rect
HPDF_ToRect  (HPDF_REAL   left,
              HPDF_REAL   bottom,
              HPDF_REAL   right,
              HPDF_REAL   top)
{
    HPDF_Rect rect;

    rect.left = left;
    rect.bottom = bottom;
    rect.right = right;
    rect.top = top;

    return rect;
}