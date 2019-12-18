#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_9__ {size_t HashTableSize; TYPE_1__** FcbHashTable; int /*<<< orphan*/  FcbListHead; } ;
struct TYPE_7__ {size_t Hash; struct TYPE_7__* next; } ;
struct TYPE_8__ {scalar_t__ parentFcb; TYPE_1__ ShortHash; TYPE_1__ Hash; int /*<<< orphan*/  FcbListEntry; int /*<<< orphan*/  PathNameU; } ;
typedef  TYPE_2__* PVFATFCB ;
typedef  TYPE_3__* PDEVICE_EXTENSION ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfatGrabFCB (TYPE_3__*,scalar_t__) ; 
 size_t vfatNameHash (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
VOID
vfatAddFCBToTable(
    PDEVICE_EXTENSION pVCB,
    PVFATFCB pFCB)
{
    ULONG Index;
    ULONG ShortIndex;

    ASSERT(pFCB->Hash.Hash == vfatNameHash(0, &pFCB->PathNameU));
    Index = pFCB->Hash.Hash % pVCB->HashTableSize;
    ShortIndex = pFCB->ShortHash.Hash % pVCB->HashTableSize;

    InsertTailList(&pVCB->FcbListHead, &pFCB->FcbListEntry);

    pFCB->Hash.next = pVCB->FcbHashTable[Index];
    pVCB->FcbHashTable[Index] = &pFCB->Hash;
    if (pFCB->Hash.Hash != pFCB->ShortHash.Hash)
    {
        pFCB->ShortHash.next = pVCB->FcbHashTable[ShortIndex];
        pVCB->FcbHashTable[ShortIndex] = &pFCB->ShortHash;
    }
    if (pFCB->parentFcb)
    {
        vfatGrabFCB(pVCB, pFCB->parentFcb);
    }
}