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
struct TYPE_4__ {int bottom; int top; } ;
struct TYPE_5__ {int nItemHeight; TYPE_1__ rcList; } ;
typedef  TYPE_2__ LISTVIEW_INFO ;
typedef  int INT ;

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static inline INT LISTVIEW_GetCountPerColumn(const LISTVIEW_INFO *infoPtr)
{
    INT nListHeight = infoPtr->rcList.bottom - infoPtr->rcList.top;

    return infoPtr->nItemHeight ? max(nListHeight / infoPtr->nItemHeight, 1) : 0;
}