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
struct TYPE_9__ {TYPE_1__* entries; int /*<<< orphan*/  transactedParent; } ;
typedef  TYPE_2__ TransactedSnapshotImpl ;
struct TYPE_10__ {scalar_t__ leftChild; scalar_t__ rightChild; scalar_t__ dirRootEntry; } ;
struct TYPE_8__ {scalar_t__ read; int /*<<< orphan*/  data; int /*<<< orphan*/  transactedParentEntry; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DirRef ;
typedef  TYPE_3__ DirEntry ;

/* Variables and functions */
 scalar_t__ DIRENTRY_NULL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StorageBaseImpl_ReadDirEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ TRUE ; 
 void* TransactedSnapshotImpl_CreateStubEntry (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static HRESULT TransactedSnapshotImpl_EnsureReadEntry(
  TransactedSnapshotImpl *This, DirRef entry)
{
  HRESULT hr=S_OK;
  DirEntry data;

  if (!This->entries[entry].read)
  {
    hr = StorageBaseImpl_ReadDirEntry(This->transactedParent,
        This->entries[entry].transactedParentEntry,
        &data);

    if (SUCCEEDED(hr) && data.leftChild != DIRENTRY_NULL)
    {
      data.leftChild = TransactedSnapshotImpl_CreateStubEntry(This, data.leftChild);

      if (data.leftChild == DIRENTRY_NULL)
        hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr) && data.rightChild != DIRENTRY_NULL)
    {
      data.rightChild = TransactedSnapshotImpl_CreateStubEntry(This, data.rightChild);

      if (data.rightChild == DIRENTRY_NULL)
        hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr) && data.dirRootEntry != DIRENTRY_NULL)
    {
      data.dirRootEntry = TransactedSnapshotImpl_CreateStubEntry(This, data.dirRootEntry);

      if (data.dirRootEntry == DIRENTRY_NULL)
        hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr))
    {
      memcpy(&This->entries[entry].data, &data, sizeof(DirEntry));
      This->entries[entry].read = TRUE;
    }
  }

  return hr;
}