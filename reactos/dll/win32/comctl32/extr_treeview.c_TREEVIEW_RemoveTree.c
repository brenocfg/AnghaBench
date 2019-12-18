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
struct TYPE_4__ {scalar_t__ uNumItems; int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TREEVIEW_RemoveAllChildren (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
TREEVIEW_RemoveTree(TREEVIEW_INFO *infoPtr)
{
    TREEVIEW_RemoveAllChildren(infoPtr, infoPtr->root);

    assert(infoPtr->uNumItems == 0);	/* root isn't counted in uNumItems */
}