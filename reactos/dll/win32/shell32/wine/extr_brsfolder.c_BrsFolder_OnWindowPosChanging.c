#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_9__ {TYPE_2__ szMin; TYPE_1__* lpBrowseInfo; } ;
typedef  TYPE_3__ browse_info ;
struct TYPE_10__ {int flags; scalar_t__ cx; scalar_t__ cy; } ;
typedef  TYPE_4__ WINDOWPOS ;
struct TYPE_7__ {int ulFlags; } ;
typedef  int /*<<< orphan*/  LRESULT ;

/* Variables and functions */
 int BIF_NEWDIALOGSTYLE ; 
 int SWP_NOSIZE ; 

__attribute__((used)) static LRESULT BrsFolder_OnWindowPosChanging(browse_info *info, WINDOWPOS *pos)
{
    if ((info->lpBrowseInfo->ulFlags & BIF_NEWDIALOGSTYLE) && !(pos->flags & SWP_NOSIZE))
    {
        if (pos->cx < info->szMin.cx)
            pos->cx = info->szMin.cx;
        if (pos->cy < info->szMin.cy)
            pos->cy = info->szMin.cy;
    }
    return 0;
}