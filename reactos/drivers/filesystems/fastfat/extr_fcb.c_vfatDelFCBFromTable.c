#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_12__ {struct TYPE_12__* next; TYPE_3__* self; } ;
struct TYPE_11__ {size_t HashTableSize; TYPE_5__** FcbHashTable; } ;
struct TYPE_9__ {size_t Hash; TYPE_5__* next; } ;
struct TYPE_8__ {size_t Hash; TYPE_5__* next; } ;
struct TYPE_10__ {int /*<<< orphan*/  FcbListEntry; TYPE_2__ Hash; TYPE_1__ ShortHash; } ;
typedef  TYPE_3__* PVFATFCB ;
typedef  TYPE_4__* PDEVICE_EXTENSION ;
typedef  TYPE_5__ HASHENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static
VOID
vfatDelFCBFromTable(
    PDEVICE_EXTENSION pVCB,
    PVFATFCB pFCB)
{
    ULONG Index;
    ULONG ShortIndex;
    HASHENTRY* entry;

    Index = pFCB->Hash.Hash % pVCB->HashTableSize;
    ShortIndex = pFCB->ShortHash.Hash % pVCB->HashTableSize;

    if (pFCB->Hash.Hash != pFCB->ShortHash.Hash)
    {
        entry = pVCB->FcbHashTable[ShortIndex];
        if (entry->self == pFCB)
        {
            pVCB->FcbHashTable[ShortIndex] = entry->next;
        }
        else
        {
            while (entry->next->self != pFCB)
            {
                entry = entry->next;
            }
            entry->next = pFCB->ShortHash.next;
        }
    }
    entry = pVCB->FcbHashTable[Index];
    if (entry->self == pFCB)
    {
        pVCB->FcbHashTable[Index] = entry->next;
    }
    else
    {
        while (entry->next->self != pFCB)
        {
            entry = entry->next;
        }
        entry->next = pFCB->Hash.next;
    }

    RemoveEntryList(&pFCB->FcbListEntry);
}