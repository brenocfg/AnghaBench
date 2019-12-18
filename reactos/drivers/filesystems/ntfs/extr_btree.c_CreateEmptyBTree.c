#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int KeyCount; struct TYPE_7__* RootNode; int /*<<< orphan*/  DiskNeedsUpdating; scalar_t__ FirstKey; } ;
typedef  scalar_t__ PB_TREE_KEY ;
typedef  TYPE_1__* PB_TREE_FILENAME_NODE ;
typedef  TYPE_1__* PB_TREE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  B_TREE_FILENAME_NODE ;
typedef  int /*<<< orphan*/  B_TREE ;

/* Variables and functions */
 scalar_t__ CreateDummyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
CreateEmptyBTree(PB_TREE *NewTree)
{
    PB_TREE Tree = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE), TAG_NTFS);
    PB_TREE_FILENAME_NODE RootNode = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_FILENAME_NODE), TAG_NTFS);
    PB_TREE_KEY DummyKey;

    DPRINT1("CreateEmptyBTree(%p) called\n", NewTree);

    if (!Tree || !RootNode)
    {
        DPRINT1("Couldn't allocate enough memory for B-Tree!\n");
        if (Tree)
            ExFreePoolWithTag(Tree, TAG_NTFS);
        if (RootNode)
            ExFreePoolWithTag(RootNode, TAG_NTFS);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Create the dummy key
    DummyKey = CreateDummyKey(FALSE);
    if (!DummyKey)
    {
        DPRINT1("ERROR: Failed to create dummy key!\n");
        ExFreePoolWithTag(Tree, TAG_NTFS);
        ExFreePoolWithTag(RootNode, TAG_NTFS);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory(Tree, sizeof(B_TREE));
    RtlZeroMemory(RootNode, sizeof(B_TREE_FILENAME_NODE));

    // Setup the Tree
    RootNode->FirstKey = DummyKey;
    RootNode->KeyCount = 1;
    RootNode->DiskNeedsUpdating = TRUE;
    Tree->RootNode = RootNode;

    *NewTree = Tree;

    // Memory will be freed when DestroyBTree() is called

    return STATUS_SUCCESS;
}