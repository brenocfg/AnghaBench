#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
struct TYPE_10__ {TYPE_2__* RootNode; } ;
struct TYPE_9__ {int KeyCount; TYPE_1__* FirstKey; int /*<<< orphan*/  VCN; scalar_t__ HasValidVCN; } ;
struct TYPE_8__ {struct TYPE_8__* NextKey; } ;
typedef  TYPE_1__* PB_TREE_KEY ;
typedef  TYPE_2__* PB_TREE_FILENAME_NODE ;
typedef  TYPE_3__* PB_TREE ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,...) ; 
 int /*<<< orphan*/  DumpBTreeKey (TYPE_3__*,TYPE_1__*,scalar_t__,scalar_t__) ; 

VOID
DumpBTreeNode(PB_TREE Tree,
              PB_TREE_FILENAME_NODE Node,
              ULONG Number,
              ULONG Depth)
{
    PB_TREE_KEY CurrentKey;
    ULONG i;
    for (i = 0; i < Depth; i++)
        DbgPrint(" ");
    DbgPrint("Node #%d, Depth %d, has %d key%s", Number, Depth, Node->KeyCount, Node->KeyCount == 1 ? "" : "s");

    if (Node->HasValidVCN)
        DbgPrint(" VCN: %I64u\n", Node->VCN);
    else if (Tree->RootNode == Node)
        DbgPrint(" Index Root");
    else
        DbgPrint(" NOT ASSIGNED VCN YET\n");

    CurrentKey = Node->FirstKey;
    for (i = 0; i < Node->KeyCount; i++)
    {
        DumpBTreeKey(Tree, CurrentKey, i, Depth);
        CurrentKey = CurrentKey->NextKey;
    }
}