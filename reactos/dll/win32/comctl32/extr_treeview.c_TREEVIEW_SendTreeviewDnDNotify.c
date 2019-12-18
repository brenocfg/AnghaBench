#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_13__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  state; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  state; TYPE_5__* hItem; } ;
struct TYPE_12__ {int /*<<< orphan*/  hdr; TYPE_2__ ptDrag; TYPE_1__ itemNew; scalar_t__ action; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  TYPE_3__ POINT ;
typedef  TYPE_4__ NMTREEVIEWW ;
typedef  TYPE_5__* HTREEITEM ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  TREEVIEW_SendRealNotify (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int TVIF_HANDLE ; 
 int TVIF_PARAM ; 
 int TVIF_STATE ; 

__attribute__((used)) static BOOL
TREEVIEW_SendTreeviewDnDNotify(const TREEVIEW_INFO *infoPtr, UINT code,
			       HTREEITEM dragItem, POINT pt)
{
    NMTREEVIEWW nmhdr;

    TRACE("code:%d dragitem:%p\n", code, dragItem);

    nmhdr.action = 0;
    nmhdr.itemNew.mask = TVIF_STATE | TVIF_PARAM | TVIF_HANDLE;
    nmhdr.itemNew.hItem = dragItem;
    nmhdr.itemNew.state = dragItem->state;
    nmhdr.itemNew.lParam = dragItem->lParam;

    nmhdr.ptDrag.x = pt.x;
    nmhdr.ptDrag.y = pt.y;

    return TREEVIEW_SendRealNotify(infoPtr, code, &nmhdr.hdr);
}