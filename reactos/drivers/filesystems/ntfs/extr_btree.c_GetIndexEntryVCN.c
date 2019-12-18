#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG_PTR ;
typedef  int /*<<< orphan*/  ULONGLONG ;
struct TYPE_3__ {int Flags; scalar_t__ Length; } ;
typedef  int /*<<< orphan*/ * PULONGLONG ;
typedef  TYPE_1__* PINDEX_ENTRY_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int NTFS_INDEX_ENTRY_NODE ; 

ULONGLONG
GetIndexEntryVCN(PINDEX_ENTRY_ATTRIBUTE IndexEntry)
{
    PULONGLONG Destination = (PULONGLONG)((ULONG_PTR)IndexEntry + IndexEntry->Length - sizeof(ULONGLONG));

    ASSERT(IndexEntry->Flags & NTFS_INDEX_ENTRY_NODE);

    return *Destination;
}