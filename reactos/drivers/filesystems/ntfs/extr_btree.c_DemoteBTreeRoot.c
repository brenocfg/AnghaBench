#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* RootNode; } ;
struct TYPE_10__ {int KeyCount; void* DiskNeedsUpdating; struct TYPE_10__* FirstKey; struct TYPE_10__* LesserChild; } ;
typedef  TYPE_1__* PB_TREE_KEY ;
typedef  TYPE_1__* PB_TREE_FILENAME_NODE ;
typedef  TYPE_3__* PB_TREE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  B_TREE_FILENAME_NODE ;

/* Variables and functions */
 TYPE_1__* CreateDummyKey (void*) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DumpBTree (TYPE_3__*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 void* TRUE ; 

NTSTATUS
DemoteBTreeRoot(PB_TREE Tree)
{
    PB_TREE_FILENAME_NODE NewSubNode, NewIndexRoot;
    PB_TREE_KEY DummyKey;

    DPRINT("Collapsing Index Root into sub-node.\n");

#ifndef NDEBUG
    DumpBTree(Tree);
#endif

    // Create a new node that will hold the keys currently in index root
    NewSubNode = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_FILENAME_NODE), TAG_NTFS);
    if (!NewSubNode)
    {
        DPRINT1("ERROR: Couldn't allocate memory for new sub-node.\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    RtlZeroMemory(NewSubNode, sizeof(B_TREE_FILENAME_NODE));

    // Copy the applicable data from the old index root node
    NewSubNode->KeyCount = Tree->RootNode->KeyCount;
    NewSubNode->FirstKey = Tree->RootNode->FirstKey;
    NewSubNode->DiskNeedsUpdating = TRUE;

    // Create a new dummy key, and make the new node it's child
    DummyKey = CreateDummyKey(TRUE);
    if (!DummyKey)
    {
        DPRINT1("ERROR: Couldn't allocate memory for new root node.\n");
        ExFreePoolWithTag(NewSubNode, TAG_NTFS);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Make the new node a child of the dummy key
    DummyKey->LesserChild = NewSubNode;

    // Create a new index root node
    NewIndexRoot = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_FILENAME_NODE), TAG_NTFS);
    if (!NewIndexRoot)
    {
        DPRINT1("ERROR: Couldn't allocate memory for new index root.\n");
        ExFreePoolWithTag(NewSubNode, TAG_NTFS);
        ExFreePoolWithTag(DummyKey, TAG_NTFS);
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    RtlZeroMemory(NewIndexRoot, sizeof(B_TREE_FILENAME_NODE));

    NewIndexRoot->DiskNeedsUpdating = TRUE;

    // Insert the dummy key into the new node
    NewIndexRoot->FirstKey = DummyKey;
    NewIndexRoot->KeyCount = 1;
    NewIndexRoot->DiskNeedsUpdating = TRUE;

    // Make the new node the Tree's root node
    Tree->RootNode = NewIndexRoot;

#ifndef NDEBUG
    DumpBTree(Tree);
#endif

    return STATUS_SUCCESS;
}