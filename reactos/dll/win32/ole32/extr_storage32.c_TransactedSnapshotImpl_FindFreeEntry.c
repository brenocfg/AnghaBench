#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_8__ {size_t firstFreeEntry; size_t entries_size; TYPE_2__* entries; } ;
typedef  TYPE_1__ TransactedSnapshotImpl ;
struct TYPE_9__ {scalar_t__ inuse; } ;
typedef  TYPE_2__ TransactedDirEntry ;
typedef  size_t DirRef ;

/* Variables and functions */
 size_t DIRENTRY_NULL ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static DirRef TransactedSnapshotImpl_FindFreeEntry(TransactedSnapshotImpl *This)
{
  DirRef result=This->firstFreeEntry;

  while (result < This->entries_size && This->entries[result].inuse)
    result++;

  if (result == This->entries_size)
  {
    ULONG new_size = This->entries_size * 2;
    TransactedDirEntry *new_entries;

    new_entries = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TransactedDirEntry) * new_size);
    if (!new_entries) return DIRENTRY_NULL;

    memcpy(new_entries, This->entries, sizeof(TransactedDirEntry) * This->entries_size);
    HeapFree(GetProcessHeap(), 0, This->entries);

    This->entries = new_entries;
    This->entries_size = new_size;
  }

  This->entries[result].inuse = TRUE;

  This->firstFreeEntry = result+1;

  return result;
}