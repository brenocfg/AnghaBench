#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ cChildren; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ I_CHILDRENCALLBACK ; 
 int /*<<< orphan*/  TREEVIEW_UpdateDispInfo (int /*<<< orphan*/  const*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVIF_CHILDREN ; 

__attribute__((used)) static BOOL
TREEVIEW_HasChildren(const TREEVIEW_INFO *infoPtr, TREEVIEW_ITEM *item)
{
    TREEVIEW_UpdateDispInfo(infoPtr, item, TVIF_CHILDREN);
    /* Protect for a case when callback field is not changed by a host,
       otherwise negative values trigger normal notifications. */
    return item->cChildren != 0 && item->cChildren != I_CHILDRENCALLBACK;
}