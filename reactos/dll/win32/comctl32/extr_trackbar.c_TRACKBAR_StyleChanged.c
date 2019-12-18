#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WPARAM ;
struct TYPE_6__ {int /*<<< orphan*/  styleNew; } ;
struct TYPE_5__ {int /*<<< orphan*/  dwStyle; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  TYPE_2__ STYLESTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 scalar_t__ GWL_STYLE ; 

__attribute__((used)) static LRESULT
TRACKBAR_StyleChanged (TRACKBAR_INFO *infoPtr, WPARAM wStyleType,
                       const STYLESTRUCT *lpss)
{
    if (wStyleType != GWL_STYLE) return 0;

    infoPtr->dwStyle = lpss->styleNew;

    return 0;
}