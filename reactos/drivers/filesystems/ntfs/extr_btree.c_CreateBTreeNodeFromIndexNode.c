#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_21__ {scalar_t__ BytesPerIndexRecord; } ;
struct TYPE_25__ {TYPE_1__ NtfsInfo; } ;
struct TYPE_22__ {scalar_t__ TotalSizeOfEntries; scalar_t__ FirstEntryOffset; } ;
struct TYPE_20__ {scalar_t__ Type; } ;
struct TYPE_24__ {scalar_t__ VCN; int /*<<< orphan*/  HasValidVCN; TYPE_3__* IndexEntry; struct TYPE_24__* LesserChild; struct TYPE_24__* NextKey; int /*<<< orphan*/  KeyCount; TYPE_2__ Header; TYPE_14__ Ntfs; struct TYPE_24__* FirstKey; } ;
struct TYPE_23__ {int Length; int Flags; } ;
typedef  scalar_t__* PULONGLONG ;
typedef  int /*<<< orphan*/ * PNTFS_ATTR_CONTEXT ;
typedef  int /*<<< orphan*/  PINDEX_ROOT_ATTRIBUTE ;
typedef  TYPE_3__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  TYPE_4__* PINDEX_BUFFER ;
typedef  TYPE_5__* PDEVICE_EXTENSION ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  TYPE_4__* PB_TREE_KEY ;
typedef  TYPE_4__* PB_TREE_FILENAME_NODE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  B_TREE_KEY ;
typedef  int /*<<< orphan*/  B_TREE_FILENAME_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DestroyBTreeNode (TYPE_4__*) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FixupUpdateSequenceArray (TYPE_5__*,TYPE_14__*) ; 
 int /*<<< orphan*/  GetAllocationOffsetFromVCN (TYPE_5__*,scalar_t__,scalar_t__) ; 
 scalar_t__ NRH_INDX_TYPE ; 
 int NTFS_INDEX_ENTRY_END ; 
 int NTFS_INDEX_ENTRY_NODE ; 
 int /*<<< orphan*/  NT_ASSERT (int) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 scalar_t__ ReadAttribute (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_4__*,int) ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  TRUE ; 

PB_TREE_FILENAME_NODE
CreateBTreeNodeFromIndexNode(PDEVICE_EXTENSION Vcb,
                             PINDEX_ROOT_ATTRIBUTE IndexRoot,
                             PNTFS_ATTR_CONTEXT IndexAllocationAttributeCtx,
                             PINDEX_ENTRY_ATTRIBUTE NodeEntry)
{
    PB_TREE_FILENAME_NODE NewNode;
    PINDEX_ENTRY_ATTRIBUTE CurrentNodeEntry;
    PINDEX_ENTRY_ATTRIBUTE FirstNodeEntry;
    ULONG CurrentEntryOffset = 0;
    PINDEX_BUFFER NodeBuffer;
    ULONG IndexBufferSize = Vcb->NtfsInfo.BytesPerIndexRecord;
    PULONGLONG VCN;
    PB_TREE_KEY CurrentKey;
    NTSTATUS Status;
    ULONGLONG IndexNodeOffset;
    ULONG BytesRead;

    if (IndexAllocationAttributeCtx == NULL)
    {
        DPRINT1("ERROR: Couldn't find index allocation attribute even though there should be one!\n");
        return NULL;
    }

    // Get the node number from the end of the node entry
    VCN = (PULONGLONG)((ULONG_PTR)NodeEntry + NodeEntry->Length - sizeof(ULONGLONG));

    // Create the new tree node
    NewNode = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_FILENAME_NODE), TAG_NTFS);
    if (!NewNode)
    {
        DPRINT1("ERROR: Couldn't allocate memory for new filename node.\n");
        return NULL;
    }
    RtlZeroMemory(NewNode, sizeof(B_TREE_FILENAME_NODE));

    // Create the first key
    CurrentKey = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_KEY), TAG_NTFS);
    if (!CurrentKey)
    {
        DPRINT1("ERROR: Failed to allocate memory for key!\n");
        ExFreePoolWithTag(NewNode, TAG_NTFS);
        return NULL;
    }
    RtlZeroMemory(CurrentKey, sizeof(B_TREE_KEY));
    NewNode->FirstKey = CurrentKey;

    // Allocate memory for the node buffer
    NodeBuffer = ExAllocatePoolWithTag(NonPagedPool, IndexBufferSize, TAG_NTFS);
    if (!NodeBuffer)
    {
        DPRINT1("ERROR: Couldn't allocate memory for node buffer!\n");
        ExFreePoolWithTag(CurrentKey, TAG_NTFS);
        ExFreePoolWithTag(NewNode, TAG_NTFS);
        return NULL;
    }

    // Calculate offset into index allocation
    IndexNodeOffset = GetAllocationOffsetFromVCN(Vcb, IndexBufferSize, *VCN);

    // TODO: Confirm index bitmap has this node marked as in-use

    // Read the node
    BytesRead = ReadAttribute(Vcb,
                              IndexAllocationAttributeCtx,
                              IndexNodeOffset,
                              (PCHAR)NodeBuffer,
                              IndexBufferSize);

    ASSERT(BytesRead == IndexBufferSize);
    NT_ASSERT(NodeBuffer->Ntfs.Type == NRH_INDX_TYPE);
    NT_ASSERT(NodeBuffer->VCN == *VCN);

    // Apply the fixup array to the node buffer
    Status = FixupUpdateSequenceArray(Vcb, &NodeBuffer->Ntfs);
    if (!NT_SUCCESS(Status))
    {
        DPRINT1("ERROR: Couldn't apply fixup array to index node buffer!\n");
        ExFreePoolWithTag(NodeBuffer, TAG_NTFS);
        ExFreePoolWithTag(CurrentKey, TAG_NTFS);
        ExFreePoolWithTag(NewNode, TAG_NTFS);
        return NULL;
    }

    // Walk through the index and create keys for all the entries
    FirstNodeEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)(&NodeBuffer->Header)
                                               + NodeBuffer->Header.FirstEntryOffset);
    CurrentNodeEntry = FirstNodeEntry;
    while (CurrentEntryOffset < NodeBuffer->Header.TotalSizeOfEntries)
    {
        // Allocate memory for the current entry
        CurrentKey->IndexEntry = ExAllocatePoolWithTag(NonPagedPool, CurrentNodeEntry->Length, TAG_NTFS);
        if (!CurrentKey->IndexEntry)
        {
            DPRINT1("ERROR: Couldn't allocate memory for next key!\n");
            DestroyBTreeNode(NewNode);
            ExFreePoolWithTag(NodeBuffer, TAG_NTFS);
            return NULL;
        }

        NewNode->KeyCount++;

        // If this isn't the last entry
        if (!(CurrentNodeEntry->Flags & NTFS_INDEX_ENTRY_END))
        {
            // Create the next key
            PB_TREE_KEY NextKey = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_KEY), TAG_NTFS);
            if (!NextKey)
            {
                DPRINT1("ERROR: Couldn't allocate memory for next key!\n");
                DestroyBTreeNode(NewNode);
                ExFreePoolWithTag(NodeBuffer, TAG_NTFS);
                return NULL;
            }
            RtlZeroMemory(NextKey, sizeof(B_TREE_KEY));

            // Add NextKey to the end of the list
            CurrentKey->NextKey = NextKey;

            // Copy the current entry to its key
            RtlCopyMemory(CurrentKey->IndexEntry, CurrentNodeEntry, CurrentNodeEntry->Length);

            // See if the current key has a sub-node
            if (CurrentKey->IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE)
            {
                CurrentKey->LesserChild = CreateBTreeNodeFromIndexNode(Vcb,
                                                                       IndexRoot,
                                                                       IndexAllocationAttributeCtx,
                                                                       CurrentKey->IndexEntry);
            }

            CurrentKey = NextKey;
        }
        else
        {
            // Copy the final entry to its key
            RtlCopyMemory(CurrentKey->IndexEntry, CurrentNodeEntry, CurrentNodeEntry->Length);
            CurrentKey->NextKey = NULL;

            // See if the current key has a sub-node
            if (CurrentKey->IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE)
            {
                CurrentKey->LesserChild = CreateBTreeNodeFromIndexNode(Vcb,
                                                                       IndexRoot,
                                                                       IndexAllocationAttributeCtx,
                                                                       CurrentKey->IndexEntry);
            }

            break;
        }

        // Advance to the next entry
        CurrentEntryOffset += CurrentNodeEntry->Length;
        CurrentNodeEntry = (PINDEX_ENTRY_ATTRIBUTE)((ULONG_PTR)CurrentNodeEntry + CurrentNodeEntry->Length);
    }

    NewNode->VCN = *VCN;
    NewNode->HasValidVCN = TRUE;

    ExFreePoolWithTag(NodeBuffer, TAG_NTFS);

    return NewNode;
}