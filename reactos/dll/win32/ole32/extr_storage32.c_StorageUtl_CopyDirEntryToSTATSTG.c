#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int stgType; scalar_t__* name; int /*<<< orphan*/  clsid; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int type; scalar_t__ reserved; scalar_t__ grfStateBits; int /*<<< orphan*/  clsid; scalar_t__ grfLocksSupported; scalar_t__ grfMode; int /*<<< orphan*/  cbSize; scalar_t__ pwcsName; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  TYPE_1__ STATSTG ;
typedef  TYPE_2__ DirEntry ;

/* Variables and functions */
 scalar_t__ CoTaskMemAlloc (int) ; 
 int STATFLAG_NONAME ; 
#define  STGTY_ROOT 130 
#define  STGTY_STORAGE 129 
#define  STGTY_STREAM 128 
 int /*<<< orphan*/  StorageBaseImpl_GetFilename (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  lstrcpyW (scalar_t__,scalar_t__*) ; 
 int lstrlenW (scalar_t__*) ; 

void StorageUtl_CopyDirEntryToSTATSTG(
  StorageBaseImpl*      storage,
  STATSTG*              destination,
  const DirEntry*       source,
  int                   statFlags)
{
  /*
   * The copy of the string occurs only when the flag is not set
   */
  if (!(statFlags & STATFLAG_NONAME) && source->stgType == STGTY_ROOT)
  {
    /* Use the filename for the root storage. */
    destination->pwcsName = 0;
    StorageBaseImpl_GetFilename(storage, &destination->pwcsName);
  }
  else if( ((statFlags & STATFLAG_NONAME) != 0) ||
       (source->name[0] == 0) )
  {
    destination->pwcsName = 0;
  }
  else
  {
    destination->pwcsName =
      CoTaskMemAlloc((lstrlenW(source->name)+1)*sizeof(WCHAR));

    lstrcpyW(destination->pwcsName, source->name);
  }

  switch (source->stgType)
  {
    case STGTY_STORAGE:
    case STGTY_ROOT:
      destination->type = STGTY_STORAGE;
      break;
    case STGTY_STREAM:
      destination->type = STGTY_STREAM;
      break;
    default:
      destination->type = STGTY_STREAM;
      break;
  }

  destination->cbSize            = source->size;
/*
  currentReturnStruct->mtime     = {0}; TODO
  currentReturnStruct->ctime     = {0};
  currentReturnStruct->atime     = {0};
*/
  destination->grfMode           = 0;
  destination->grfLocksSupported = 0;
  destination->clsid             = source->clsid;
  destination->grfStateBits      = 0;
  destination->reserved          = 0;
}