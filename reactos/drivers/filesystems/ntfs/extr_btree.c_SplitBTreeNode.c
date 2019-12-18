#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONGLONG ;
typedef  scalar_t__ ULONG ;
struct TYPE_22__ {TYPE_2__* IndexEntry; TYPE_2__* LesserChild; struct TYPE_22__* NextKey; } ;
struct TYPE_20__ {int /*<<< orphan*/  Name; int /*<<< orphan*/  NameLength; } ;
struct TYPE_21__ {scalar_t__ KeyCount; int Length; int Flags; TYPE_3__* FirstKey; int /*<<< orphan*/  VCN; TYPE_1__ FileName; int /*<<< orphan*/  DiskNeedsUpdating; } ;
typedef  TYPE_2__* PINDEX_ENTRY_ATTRIBUTE ;
typedef  TYPE_3__* PB_TREE_KEY ;
typedef  TYPE_2__* PB_TREE_FILENAME_NODE ;
typedef  int /*<<< orphan*/  PB_TREE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  B_TREE_FILENAME_NODE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BooleanFlagOn (int,int) ; 
 void* CountBTreeKeys (TYPE_3__*) ; 
 TYPE_3__* CreateDummyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_3__**,TYPE_2__**,char*) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  DumpBTreeNode (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetIndexEntryVCN (TYPE_2__*) ; 
 int NTFS_INDEX_ENTRY_NODE ; 
 int /*<<< orphan*/  NonPagedPool ; 
 int /*<<< orphan*/  RtlCopyMemory (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  STATUS_INSUFFICIENT_RESOURCES ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetIndexEntryVCN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_NTFS ; 
 int /*<<< orphan*/  TRUE ; 

NTSTATUS
SplitBTreeNode(PB_TREE Tree,
               PB_TREE_FILENAME_NODE Node,
               PB_TREE_KEY *MedianKey,
               PB_TREE_FILENAME_NODE *NewRightHandSibling,
               BOOLEAN CaseSensitive)
{
    ULONG MedianKeyIndex;
    PB_TREE_KEY LastKeyBeforeMedian, FirstKeyAfterMedian;
    ULONG KeyCount;
    ULONG HalfSize;
    ULONG SizeSum;
    ULONG i;

    DPRINT("SplitBTreeNode(%p, %p, %p, %p, %s) called\n",
            Tree,
            Node,
            MedianKey,
            NewRightHandSibling,
            CaseSensitive ? "TRUE" : "FALSE");

#ifndef NDEBUG
    DumpBTreeNode(Node, 0, 0);
#endif

    // Create the right hand sibling
    *NewRightHandSibling = ExAllocatePoolWithTag(NonPagedPool, sizeof(B_TREE_FILENAME_NODE), TAG_NTFS);
    if (*NewRightHandSibling == NULL)
    {
        DPRINT1("Error: Failed to allocate memory for right hand sibling!\n");
        return STATUS_INSUFFICIENT_RESOURCES;
    }
    RtlZeroMemory(*NewRightHandSibling, sizeof(B_TREE_FILENAME_NODE));
    (*NewRightHandSibling)->DiskNeedsUpdating = TRUE;


    // Find the last key before the median

    // This is roughly how NTFS-3G calculates median, and it's not congruent with what Windows does:
    /*
    // find the median key index
    MedianKeyIndex = (Node->KeyCount + 1) / 2;
    MedianKeyIndex--;

    LastKeyBeforeMedian = Node->FirstKey;
    for (i = 0; i < MedianKeyIndex - 1; i++)
        LastKeyBeforeMedian = LastKeyBeforeMedian->NextKey;*/

    // The method we'll use is a little bit closer to how Windows determines the median but it's not identical.
    // What Windows does is actually more complicated than this, I think because Windows allocates more slack space to Odd-numbered
    // Index Records, leaving less room for index entries in these records (I haven't discovered why this is done).
    // (Neither Windows nor chkdsk complain if we choose a different median than Windows would have chosen, as our median will be in the ballpark)

    // Use size to locate the median key / index
    LastKeyBeforeMedian = Node->FirstKey;
    MedianKeyIndex = 0;
    HalfSize = 2016; // half the allocated size after subtracting the first index entry offset (TODO: MATH)
    SizeSum = 0;
    for (i = 0; i < Node->KeyCount; i++)
    {
        SizeSum += LastKeyBeforeMedian->IndexEntry->Length;

        if (SizeSum > HalfSize)
            break;

        MedianKeyIndex++;
        LastKeyBeforeMedian = LastKeyBeforeMedian->NextKey;
    }

    // Now we can get the median key and the key that follows it
    *MedianKey = LastKeyBeforeMedian->NextKey;
    FirstKeyAfterMedian = (*MedianKey)->NextKey;

    DPRINT1("%lu keys, %lu median\n", Node->KeyCount, MedianKeyIndex);
    DPRINT1("\t\tMedian: %.*S\n", (*MedianKey)->IndexEntry->FileName.NameLength, (*MedianKey)->IndexEntry->FileName.Name);

    // "Node" will be the left hand sibling after the split, containing all keys prior to the median key

    // We need to create a dummy pointer at the end of the LHS. The dummy's child will be the median's child.
    LastKeyBeforeMedian->NextKey = CreateDummyKey(BooleanFlagOn((*MedianKey)->IndexEntry->Flags, NTFS_INDEX_ENTRY_NODE));
    if (LastKeyBeforeMedian->NextKey == NULL)
    {
        DPRINT1("Error: Couldn't allocate dummy key!\n");
        LastKeyBeforeMedian->NextKey = *MedianKey;
        ExFreePoolWithTag(*NewRightHandSibling, TAG_NTFS);
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    // Did the median key have a child node?
    if ((*MedianKey)->IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE)
    {
        // Set the child of the new dummy key
        LastKeyBeforeMedian->NextKey->LesserChild = (*MedianKey)->LesserChild;

        // Give the dummy key's index entry the same sub-node VCN the median
        SetIndexEntryVCN(LastKeyBeforeMedian->NextKey->IndexEntry, GetIndexEntryVCN((*MedianKey)->IndexEntry));
    }
    else
    {
        // Median key didn't have a child node, but it will. Create a new index entry large enough to store a VCN.
        PINDEX_ENTRY_ATTRIBUTE NewIndexEntry = ExAllocatePoolWithTag(NonPagedPool,
                                                                     (*MedianKey)->IndexEntry->Length + sizeof(ULONGLONG),
                                                                     TAG_NTFS);
        if (!NewIndexEntry)
        {
            DPRINT1("Unable to allocate memory for new index entry!\n");
            LastKeyBeforeMedian->NextKey = *MedianKey;
            ExFreePoolWithTag(*NewRightHandSibling, TAG_NTFS);
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        // Copy the old index entry to the new one
        RtlCopyMemory(NewIndexEntry, (*MedianKey)->IndexEntry, (*MedianKey)->IndexEntry->Length);

        // Use the new index entry after freeing the old one
        ExFreePoolWithTag((*MedianKey)->IndexEntry, TAG_NTFS);
        (*MedianKey)->IndexEntry = NewIndexEntry;

        // Update the length for the VCN
        (*MedianKey)->IndexEntry->Length += sizeof(ULONGLONG);

        // Set the node flag
        (*MedianKey)->IndexEntry->Flags |= NTFS_INDEX_ENTRY_NODE;
    }

    // "Node" will become the child of the median key
    (*MedianKey)->LesserChild = Node;
    SetIndexEntryVCN((*MedianKey)->IndexEntry, Node->VCN);

    // Update Node's KeyCount (remember to add 1 for the new dummy key)
    Node->KeyCount = MedianKeyIndex + 2;

    KeyCount = CountBTreeKeys(Node->FirstKey);
    ASSERT(Node->KeyCount == KeyCount);

    // everything to the right of MedianKey becomes the right hand sibling of Node
    (*NewRightHandSibling)->FirstKey = FirstKeyAfterMedian;
    (*NewRightHandSibling)->KeyCount = CountBTreeKeys(FirstKeyAfterMedian);

#ifndef NDEBUG
    DPRINT1("Left-hand node after split:\n");
    DumpBTreeNode(Node, 0, 0);

    DPRINT1("Right-hand sibling node after split:\n");
    DumpBTreeNode(*NewRightHandSibling, 0, 0);
#endif

    return STATUS_SUCCESS;
}