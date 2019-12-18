#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cx; int cy; } ;
struct TYPE_5__ {TYPE_1__ dim; } ;
typedef  TYPE_2__ MONTHCAL_INFO ;
typedef  int INT ;

/* Variables and functions */

__attribute__((used)) static inline INT MONTHCAL_GetCalCount(const MONTHCAL_INFO *infoPtr)
{
   return infoPtr->dim.cx * infoPtr->dim.cy;
}