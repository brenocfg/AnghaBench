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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_5__ {TYPE_1__ rect; int /*<<< orphan*/  iImage; int /*<<< orphan*/  pszText; int /*<<< orphan*/  dwState; } ;
typedef  TYPE_2__ TAB_ITEM ;
typedef  int /*<<< orphan*/  TAB_INFO ;

/* Variables and functions */
 TYPE_2__* TAB_GetItem (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tab ; 

__attribute__((used)) static void
TAB_DumpItemInternal(const TAB_INFO *infoPtr, UINT iItem)
{
    if (TRACE_ON(tab)) {
	TAB_ITEM *ti = TAB_GetItem(infoPtr, iItem);

	TRACE("tab %d, dwState=0x%08x, pszText=%s, iImage=%d\n",
	      iItem, ti->dwState, debugstr_w(ti->pszText), ti->iImage);
	TRACE("tab %d, rect.left=%d, rect.top(row)=%d\n",
	      iItem, ti->rect.left, ti->rect.top);
    }
}