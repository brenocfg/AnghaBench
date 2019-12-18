#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_16__ {scalar_t__ KeyCount; void* DiskNeedsUpdating; int /*<<< orphan*/  VCN; void* HasValidVCN; TYPE_3__* FirstKey; } ;
struct TYPE_15__ {struct TYPE_15__* NextKey; TYPE_1__* IndexEntry; TYPE_4__* LesserChild; } ;
struct TYPE_14__ {int Length; int /*<<< orphan*/  Flags; } ;
typedef  int /*<<< orphan*/  PUCHAR ;
typedef  int /*<<< orphan*/  PNTFS_ATTR_CONTEXT ;
typedef  TYPE_1__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  TYPE_1__* PINDEX_BUFFER ;
typedef  int /*<<< orphan*/  PFILE_RECORD_HEADER ;
typedef  int /*<<< orphan*/  PDEVICE_EXTENSION ;
typedef  TYPE_3__* PB_TREE_KEY ;
typedef  TYPE_4__* PB_TREE_FILENAME_NODE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  void* BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (TYPE_3__*) ; 
 int /*<<< orphan*/  AllocateIndexNode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BooleanFlagOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateIndexBufferFromBTreeNode (int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetAllocationOffsetFromVCN (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTFS_INDEX_ENTRY_NODE ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  STATUS_END_OF_FILE ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetIndexEntryVCN (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 void* TRUE ; 
 int /*<<< orphan*/  WriteAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

NTSTATUS
UpdateIndexNode(PDEVICE_EXTENSION DeviceExt,
                PFILE_RECORD_HEADER FileRecord,
                PB_TREE_FILENAME_NODE Node,
                ULONG IndexBufferSize,
                PNTFS_ATTR_CONTEXT IndexAllocationContext,
                ULONG IndexAllocationOffset)
{
    ULONG i;
    PB_TREE_KEY CurrentKey = Node->FirstKey;
    BOOLEAN HasChildren = FALSE;
    NTSTATUS Status;


    DPRINT("UpdateIndexNode(%p, %p, %p, %lu, %p, %lu) called for index node with VCN %I64u\n",
           DeviceExt,
           FileRecord,
           Node,
           IndexBufferSize,
           IndexAllocationContext,
           IndexAllocationOffset,
           Node->VCN);

    // Walk through the node and look for children to update
    for (i = 0; i < Node->KeyCount; i++)
    {
        ASSERT(CurrentKey);

        // If there's a child node
        if (CurrentKey->LesserChild)
        {
            HasChildren = TRUE;

            // Update the child node on disk
            Status = UpdateIndexNode(DeviceExt, FileRecord, CurrentKey->LesserChild, IndexBufferSize, IndexAllocationContext, IndexAllocationOffset);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("ERROR: Failed to update child node!\n");
                return Status;
            }
            
            // Is the Index Entry large enough to store the VCN?
            if (!BooleanFlagOn(CurrentKey->IndexEntry->Flags, NTFS_INDEX_ENTRY_NODE))
            {
                // Allocate memory for the larger index entry
                PINDEX_ENTRY_ATTRIBUTE NewEntry = ExAllocatePoolWithTag(NonPagedPool,
                                                                        CurrentKey->IndexEntry->Length + sizeof(ULONGLONG),
                                                                        TAG_NTFS);
                if (!NewEntry)
                {
                    DPRINT1("ERROR: Unable to allocate memory for new index entry!\n");
                    return STATUS_INSUFFICIENT_RESOURCES;
                }

                // Copy the old entry to the new one
                RtlCopyMemory(NewEntry, CurrentKey->IndexEntry, CurrentKey->IndexEntry->Length);

                NewEntry->Length += sizeof(ULONGLONG);

                // Free the old memory
                ExFreePoolWithTag(CurrentKey->IndexEntry, TAG_NTFS);

                CurrentKey->IndexEntry = NewEntry;
            }

            // Update the VCN stored in the index entry of CurrentKey
            SetIndexEntryVCN(CurrentKey->IndexEntry, CurrentKey->LesserChild->VCN);

            CurrentKey->IndexEntry->Flags |= NTFS_INDEX_ENTRY_NODE;
        }

        CurrentKey = CurrentKey->NextKey;
    }


    // Do we need to write this node to disk?
    if (Node->DiskNeedsUpdating)
    {
        ULONGLONG NodeOffset;
        ULONG LengthWritten;
        PINDEX_BUFFER IndexBuffer;

        // Does the node need to be assigned a VCN?
        if (!Node->HasValidVCN)
        {
            // Allocate the node
            Status = AllocateIndexNode(DeviceExt,
                                       FileRecord,
                                       IndexBufferSize,
                                       IndexAllocationContext,
                                       IndexAllocationOffset,
                                       &Node->VCN);
            if (!NT_SUCCESS(Status))
            {
                DPRINT1("ERROR: Failed to allocate index record in index allocation!\n");
                return Status;
            }

            Node->HasValidVCN = TRUE;
        }

        // Allocate memory for an index buffer
        IndexBuffer = ExAllocatePoolWithTag(NonPagedPool, IndexBufferSize, TAG_NTFS);
        if (!IndexBuffer)
        {
            DPRINT1("ERROR: Failed to allocate %lu bytes for index buffer!\n", IndexBufferSize);
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        // Create the index buffer we'll be writing to disk to represent this node
        Status = CreateIndexBufferFromBTreeNode(DeviceExt, Node, IndexBufferSize, HasChildren, IndexBuffer);
        if (!NT_SUCCESS(Status))
        {
            DPRINT1("ERROR: Failed to create index buffer from node!\n");
            ExFreePoolWithTag(IndexBuffer, TAG_NTFS);
            return Status;
        }

        // Get Offset of index buffer in index allocation
        NodeOffset = GetAllocationOffsetFromVCN(DeviceExt, IndexBufferSize, Node->VCN);

        // Write the buffer to the index allocation
        Status = WriteAttribute(DeviceExt, IndexAllocationContext, NodeOffset, (const PUCHAR)IndexBuffer, IndexBufferSize, &LengthWritten, FileRecord);
        if (!NT_SUCCESS(Status) || LengthWritten != IndexBufferSize)
        {
            DPRINT1("ERROR: Failed to update index allocation!\n");
            ExFreePoolWithTag(IndexBuffer, TAG_NTFS);
            if (!NT_SUCCESS(Status))
                return Status;
            else
                return STATUS_END_OF_FILE;
        }

        Node->DiskNeedsUpdating = FALSE;

        // Free the index buffer
        ExFreePoolWithTag(IndexBuffer, TAG_NTFS);
    }

    return STATUS_SUCCESS;
}