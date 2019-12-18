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
typedef  void* HPDF_INT16 ;
typedef  TYPE_1__ HPDF_Box ;

/* Variables and functions */

HPDF_Box
HPDF_ToBox  (HPDF_INT16   left,
             HPDF_INT16   bottom,
             HPDF_INT16   right,
             HPDF_INT16   top)
{
    HPDF_Box box;

    box.left = left;
    box.bottom = bottom;
    box.right = right;
    box.top = top;

    return box;
}