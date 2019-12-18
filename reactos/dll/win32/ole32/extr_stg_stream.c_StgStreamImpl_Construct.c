#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ LowPart; scalar_t__ HighPart; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {TYPE_2__ currentPosition; int /*<<< orphan*/  dirEntry; int /*<<< orphan*/  grfMode; int /*<<< orphan*/ * parentStorage; scalar_t__ ref; TYPE_3__ IStream_iface; } ;
typedef  int /*<<< orphan*/  StorageBaseImpl ;
typedef  TYPE_4__ StgStreamImpl ;
typedef  int /*<<< orphan*/  DirRef ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StgStreamVtbl ; 
 int /*<<< orphan*/  StorageBaseImpl_AddStream (int /*<<< orphan*/ *,TYPE_4__*) ; 

StgStreamImpl* StgStreamImpl_Construct(
		StorageBaseImpl* parentStorage,
    DWORD            grfMode,
    DirRef           dirEntry)
{
  StgStreamImpl* newStream;

  newStream = HeapAlloc(GetProcessHeap(), 0, sizeof(StgStreamImpl));

  if (newStream)
  {
    /*
     * Set-up the virtual function table and reference count.
     */
    newStream->IStream_iface.lpVtbl = &StgStreamVtbl;
    newStream->ref       = 0;

    newStream->parentStorage = parentStorage;

    /*
     * We want to nail-down the reference to the storage in case the
     * stream out-lives the storage in the client application.
     *
     * -- IStorage_AddRef(&newStream->parentStorage->IStorage_iface);
     *
     * No, don't do this. Some apps call IStorage_Release without
     * calling IStream_Release first. If we grab a reference the
     * file is not closed, and the app fails when it tries to
     * reopen the file (Easy-PC, for example)
     */

    newStream->grfMode = grfMode;
    newStream->dirEntry = dirEntry;

    /*
     * Start the stream at the beginning.
     */
    newStream->currentPosition.u.HighPart = 0;
    newStream->currentPosition.u.LowPart = 0;

    /* add us to the storage's list of active streams */
    StorageBaseImpl_AddStream(parentStorage, newStream);
  }

  return newStream;
}