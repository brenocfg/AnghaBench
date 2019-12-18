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
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int dwStyle; } ;
struct TYPE_7__ {void* y; void* x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  void* INT ;
typedef  TYPE_2__ HEADER_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  HDN_DIVIDERDBLCLICKW ; 
 int /*<<< orphan*/  HDN_ITEMDBLCLICKW ; 
 int HDS_BUTTONS ; 
 int /*<<< orphan*/  HEADER_InternalHitTest (TYPE_2__ const*,TYPE_1__*,scalar_t__*,void**) ; 
 int /*<<< orphan*/  HEADER_SendNotifyWithHDItemT (TYPE_2__ const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 scalar_t__ HHT_ONDIVIDER ; 
 scalar_t__ HHT_ONDIVOPEN ; 
 scalar_t__ HHT_ONHEADER ; 

__attribute__((used)) static LRESULT
HEADER_LButtonDblClk (const HEADER_INFO *infoPtr, INT x, INT y)
{
    POINT pt;
    UINT  flags;
    INT   nItem;

    pt.x = x;
    pt.y = y;
    HEADER_InternalHitTest (infoPtr, &pt, &flags, &nItem);

    if ((infoPtr->dwStyle & HDS_BUTTONS) && (flags == HHT_ONHEADER))
        HEADER_SendNotifyWithHDItemT(infoPtr, HDN_ITEMDBLCLICKW, nItem, NULL);
    else if ((flags == HHT_ONDIVIDER) || (flags == HHT_ONDIVOPEN))
        HEADER_SendNotifyWithHDItemT(infoPtr, HDN_DIVIDERDBLCLICKW, nItem, NULL);

    return 0;
}