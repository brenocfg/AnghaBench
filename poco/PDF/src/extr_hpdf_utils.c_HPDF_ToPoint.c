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
struct TYPE_3__ {void* y; void* x; } ;
typedef  TYPE_1__ HPDF_Point ;
typedef  void* HPDF_INT16 ;

/* Variables and functions */

HPDF_Point
HPDF_ToPoint  (HPDF_INT16   x,
               HPDF_INT16   y)
{
    HPDF_Point point;

    point.x = x;
    point.y = y;

    return point;
}