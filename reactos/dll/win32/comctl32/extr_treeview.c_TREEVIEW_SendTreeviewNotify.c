#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {int /*<<< orphan*/  pszText; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_11__ {TYPE_6__ itemNew; TYPE_6__ itemOld; int /*<<< orphan*/  hdr; TYPE_1__ ptDrag; int /*<<< orphan*/  action; } ;
struct TYPE_10__ {int /*<<< orphan*/  bNtfUnicode; } ;
typedef  TYPE_2__ TREEVIEW_INFO ;
typedef  TYPE_3__ NMTREEVIEWW ;
typedef  int /*<<< orphan*/  HTREEITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREEVIEW_SendRealNotify (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREEVIEW_TVItemFromItem (TYPE_2__ const*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static BOOL
TREEVIEW_SendTreeviewNotify(const TREEVIEW_INFO *infoPtr, UINT code, UINT action,
			    UINT mask, HTREEITEM oldItem, HTREEITEM newItem)
{
    NMTREEVIEWW nmhdr;
    BOOL ret;

    TRACE("code:%d action:0x%x olditem:%p newitem:%p\n",
	  code, action, oldItem, newItem);

    memset(&nmhdr, 0, sizeof(NMTREEVIEWW));
    nmhdr.action = action;

    if (oldItem)
	TREEVIEW_TVItemFromItem(infoPtr, mask, &nmhdr.itemOld, oldItem);

    if (newItem)
	TREEVIEW_TVItemFromItem(infoPtr, mask, &nmhdr.itemNew, newItem);

    nmhdr.ptDrag.x = 0;
    nmhdr.ptDrag.y = 0;

    ret = TREEVIEW_SendRealNotify(infoPtr, code, &nmhdr.hdr);
    if (!infoPtr->bNtfUnicode)
    {
        heap_free(nmhdr.itemOld.pszText);
        heap_free(nmhdr.itemNew.pszText);
    }
    return ret;
}