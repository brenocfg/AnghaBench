#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * pszText; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;

/* Variables and functions */
 int /*<<< orphan*/ * LPSTR_TEXTCALLBACKW ; 
 char const* debugstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
TREEVIEW_ItemName(const TREEVIEW_ITEM *item)
{
    if (item == NULL) return "<null item>";
    if (item->pszText == LPSTR_TEXTCALLBACKW) return "<callback>";
    if (item->pszText == NULL) return "<null>";
    return debugstr_w(item->pszText);
}