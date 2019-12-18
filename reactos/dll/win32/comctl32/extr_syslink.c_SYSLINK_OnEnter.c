#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  IgnoreReturn; scalar_t__ HasFocus; } ;
typedef  TYPE_1__ SYSLINK_INFO ;
typedef  scalar_t__ PDOC_ITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NM_RETURN ; 
 scalar_t__ SYSLINK_GetFocusLink (TYPE_1__ const*,int*) ; 
 int /*<<< orphan*/  SYSLINK_SendParentNotify (TYPE_1__ const*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL SYSLINK_OnEnter (const SYSLINK_INFO *infoPtr)
{
    if(infoPtr->HasFocus && !infoPtr->IgnoreReturn)
    {
        PDOC_ITEM Focus;
        int id;
        
        Focus = SYSLINK_GetFocusLink(infoPtr, &id);
        if(Focus)
        {
            SYSLINK_SendParentNotify(infoPtr, NM_RETURN, Focus, id);
            return TRUE;
        }
    }
    return FALSE;
}