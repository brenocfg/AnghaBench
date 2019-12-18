#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nCurrentTool; } ;
struct TYPE_7__ {scalar_t__ cbSize; } ;
typedef  TYPE_1__ TTTOOLINFOW ;
typedef  TYPE_2__ TOOLTIPS_INFO ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  TOOLTIPS_CopyInfoT (TYPE_2__ const*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TTTOOLINFOW_V1_SIZE ; 

__attribute__((used)) static LRESULT
TOOLTIPS_GetCurrentToolT (const TOOLTIPS_INFO *infoPtr, TTTOOLINFOW *ti, BOOL isW)
{
    if (ti) {
        if (ti->cbSize < TTTOOLINFOW_V1_SIZE)
            return FALSE;

        if (infoPtr->nCurrentTool != -1)
            TOOLTIPS_CopyInfoT (infoPtr, infoPtr->nCurrentTool, ti, isW);
    }

    return infoPtr->nCurrentTool != -1;
}