#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {scalar_t__ leftChild; scalar_t__ rightChild; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DirRef ;
typedef  TYPE_1__ DirEntry ;

/* Variables and functions */
 scalar_t__ DIRENTRY_NULL ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ StorageBaseImpl_ReadDirEntry (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 scalar_t__ StorageBaseImpl_WriteDirEntry (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 scalar_t__ findTreeParent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setEntryLink (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static HRESULT removeFromTree(
  StorageBaseImpl *This,
  DirRef        parentStorageIndex,
  DirRef        deletedIndex)
{
  DirEntry   entryToDelete;
  DirEntry   parentEntry;
  DirRef parentEntryRef;
  ULONG typeOfRelation;
  HRESULT hr;

  hr = StorageBaseImpl_ReadDirEntry(This, deletedIndex, &entryToDelete);

  if (hr != S_OK)
    return hr;

  /*
   * Find the element that links to the one we want to delete.
   */
  hr = findTreeParent(This, parentStorageIndex, entryToDelete.name,
    &parentEntry, &parentEntryRef, &typeOfRelation);

  if (hr != S_OK)
    return hr;

  if (entryToDelete.leftChild != DIRENTRY_NULL)
  {
    /*
     * Replace the deleted entry with its left child
     */
    setEntryLink(&parentEntry, typeOfRelation, entryToDelete.leftChild);

    hr = StorageBaseImpl_WriteDirEntry(
            This,
            parentEntryRef,
            &parentEntry);
    if(FAILED(hr))
    {
      return hr;
    }

    if (entryToDelete.rightChild != DIRENTRY_NULL)
    {
      /*
       * We need to reinsert the right child somewhere. We already know it and
       * its children are greater than everything in the left tree, so we
       * insert it at the rightmost point in the left tree.
       */
      DirRef newRightChildParent = entryToDelete.leftChild;
      DirEntry newRightChildParentEntry;

      do
      {
        hr = StorageBaseImpl_ReadDirEntry(
                This,
                newRightChildParent,
                &newRightChildParentEntry);
        if (FAILED(hr))
        {
          return hr;
        }

        if (newRightChildParentEntry.rightChild != DIRENTRY_NULL)
          newRightChildParent = newRightChildParentEntry.rightChild;
      } while (newRightChildParentEntry.rightChild != DIRENTRY_NULL);

      newRightChildParentEntry.rightChild = entryToDelete.rightChild;

      hr = StorageBaseImpl_WriteDirEntry(
              This,
              newRightChildParent,
              &newRightChildParentEntry);
      if (FAILED(hr))
      {
        return hr;
      }
    }
  }
  else
  {
    /*
     * Replace the deleted entry with its right child
     */
    setEntryLink(&parentEntry, typeOfRelation, entryToDelete.rightChild);

    hr = StorageBaseImpl_WriteDirEntry(
            This,
            parentEntryRef,
            &parentEntry);
    if(FAILED(hr))
    {
      return hr;
    }
  }

  return hr;
}