#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int LowPart; scalar_t__ HighPart; } ;
struct TYPE_11__ {TYPE_1__ u; } ;
typedef  TYPE_2__ ULARGE_INTEGER ;
struct TYPE_14__ {int smallBlockSize; } ;
struct TYPE_13__ {TYPE_2__ size; } ;
struct TYPE_12__ {int /*<<< orphan*/  ownerDirEntry; TYPE_5__* parentStorage; int /*<<< orphan*/ * headOfStreamPlaceHolder; } ;
typedef  TYPE_3__ SmallBlockChainStream ;
typedef  TYPE_4__ DirEntry ;

/* Variables and functions */
 int SmallBlockChainStream_GetCount (TYPE_3__*) ; 
 int /*<<< orphan*/  StorageImpl_ReadDirEntry (TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static ULARGE_INTEGER SmallBlockChainStream_GetSize(SmallBlockChainStream* This)
{
  DirEntry chainEntry;

  if(This->headOfStreamPlaceHolder != NULL)
  {
    ULARGE_INTEGER result;
    result.u.HighPart = 0;

    result.u.LowPart = SmallBlockChainStream_GetCount(This) *
        This->parentStorage->smallBlockSize;

    return result;
  }

  StorageImpl_ReadDirEntry(
    This->parentStorage,
    This->ownerDirEntry,
    &chainEntry);

  return chainEntry.size;
}