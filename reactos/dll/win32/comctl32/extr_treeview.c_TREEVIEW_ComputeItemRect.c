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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_10__ {int uItemHeight; int /*<<< orphan*/  clientWidth; TYPE_2__* firstVisible; } ;
struct TYPE_7__ {int top; int bottom; int /*<<< orphan*/  right; scalar_t__ left; } ;
struct TYPE_9__ {int visibleOrder; int iIntegral; TYPE_1__ rect; } ;
struct TYPE_8__ {int visibleOrder; } ;
typedef  TYPE_3__ TREEVIEW_ITEM ;
typedef  TYPE_4__ TREEVIEW_INFO ;

/* Variables and functions */

__attribute__((used)) static VOID
TREEVIEW_ComputeItemRect(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *item)
{
    item->rect.top = infoPtr->uItemHeight *
	(item->visibleOrder - infoPtr->firstVisible->visibleOrder);

    item->rect.bottom = item->rect.top
	+ infoPtr->uItemHeight * item->iIntegral - 1;

    item->rect.left = 0;
    item->rect.right = infoPtr->clientWidth;
}