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
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int Length; int MaximumLength; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_3__ UNICODE_STRING ;
typedef  scalar_t__ ULONG ;
struct TYPE_9__ {scalar_t__ LesserChild; TYPE_2__* IndexEntry; } ;
struct TYPE_6__ {int NameLength; int /*<<< orphan*/  Name; } ;
struct TYPE_7__ {int Flags; TYPE_1__ FileName; } ;
typedef  TYPE_4__* PB_TREE_KEY ;
typedef  int /*<<< orphan*/  PB_TREE ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DbgPrint (char*,...) ; 
 int /*<<< orphan*/  DumpBTreeNode (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int NTFS_INDEX_ENTRY_END ; 
 int NTFS_INDEX_ENTRY_NODE ; 

VOID
DumpBTreeKey(PB_TREE Tree, PB_TREE_KEY Key, ULONG Number, ULONG Depth)
{
    ULONG i;
    for (i = 0; i < Depth; i++)
        DbgPrint(" ");
    DbgPrint(" Key #%d", Number);

    if (!(Key->IndexEntry->Flags & NTFS_INDEX_ENTRY_END))
    {
        UNICODE_STRING FileName;
        FileName.Length = Key->IndexEntry->FileName.NameLength * sizeof(WCHAR);
        FileName.MaximumLength = FileName.Length;
        FileName.Buffer = Key->IndexEntry->FileName.Name;
        DbgPrint(" '%wZ'\n", &FileName);
    }
    else
    {
        DbgPrint(" (Dummy Key)\n");
    }

    // Is there a child node?
    if (Key->IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE)
    {
        if (Key->LesserChild)
            DumpBTreeNode(Tree, Key->LesserChild, Number, Depth + 1);
        else
        {
            // This will be an assert once nodes with arbitrary depth are debugged
            DPRINT1("DRIVER ERROR: No Key->LesserChild despite Key->IndexEntry->Flags indicating this is a node!\n");
        }
    }
}