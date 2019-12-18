#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pszText; } ;
struct TYPE_8__ {TYPE_4__ item; int /*<<< orphan*/  hdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  bNtfUnicode; } ;
typedef  int /*<<< orphan*/  TREEVIEW_ITEM ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  TYPE_2__ NMTVDISPINFOW ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TREEVIEW_SendRealNotify (TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREEVIEW_TVItemFromItem (TYPE_1__ const*,int,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int TVIF_HANDLE ; 
 int TVIF_PARAM ; 
 int TVIF_STATE ; 
 int TVIF_TEXT ; 
 int /*<<< orphan*/  TVN_BEGINLABELEDITW ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
TREEVIEW_BeginLabelEditNotify(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *editItem)
{
    NMTVDISPINFOW tvdi;
    BOOL ret;

    TREEVIEW_TVItemFromItem(infoPtr, TVIF_HANDLE | TVIF_STATE | TVIF_PARAM | TVIF_TEXT,
                            &tvdi.item, editItem);

    ret = TREEVIEW_SendRealNotify(infoPtr, TVN_BEGINLABELEDITW, &tvdi.hdr);

    if (!infoPtr->bNtfUnicode)
        heap_free(tvdi.item.pszText);

    return ret;
}