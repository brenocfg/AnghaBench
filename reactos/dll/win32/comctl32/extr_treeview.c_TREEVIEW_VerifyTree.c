#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREEVIEW_VerifyRoot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  treeview ; 

__attribute__((used)) static void
TREEVIEW_VerifyTree(TREEVIEW_INFO *infoPtr)
{
    if (!TRACE_ON(treeview)) return;

    assert(infoPtr != NULL);
    TREEVIEW_VerifyRoot(infoPtr);
}