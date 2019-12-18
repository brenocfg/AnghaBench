#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  RootNode; } ;
typedef  TYPE_1__* PB_TREE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  DumpBTreeNode (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID
DumpBTree(PB_TREE Tree)
{
    DbgPrint("B_TREE @ %p\n", Tree);
    DumpBTreeNode(Tree, Tree->RootNode, 0, 0);
}