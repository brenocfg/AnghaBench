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
struct TYPE_3__ {size_t uNumItem; size_t* order; } ;
typedef  size_t INT ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */

__attribute__((used)) static INT
HEADER_OrderToIndex(const HEADER_INFO *infoPtr, INT iorder)
{
    if ((iorder <0) || iorder >= infoPtr->uNumItem)
      return iorder;
    return infoPtr->order[iorder];
}