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
struct TYPE_3__ {int uInternalFlags; int /*<<< orphan*/  hwnd; scalar_t__ uId; } ;
typedef  TYPE_1__ TTTOOL_INFO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  SetWindowSubclass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLTIPS_SubclassProc ; 
 int TTF_IDISHWND ; 
 int TTF_SUBCLASS ; 

__attribute__((used)) static void TOOLTIPS_ResetSubclass (const TTTOOL_INFO *toolPtr)
{
    /* Reset subclassing data. */
    if (toolPtr->uInternalFlags & TTF_SUBCLASS)
        SetWindowSubclass(toolPtr->uInternalFlags & TTF_IDISHWND ? (HWND)toolPtr->uId : toolPtr->hwnd,
            TOOLTIPS_SubclassProc, 1, 0);
}