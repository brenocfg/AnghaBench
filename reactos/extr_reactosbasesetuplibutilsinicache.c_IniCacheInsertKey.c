#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* Next; struct TYPE_9__* Prev; struct TYPE_9__* Data; struct TYPE_9__* Name; } ;
typedef  TYPE_1__ WCHAR ;
struct TYPE_10__ {TYPE_1__* LastKey; TYPE_1__* FirstKey; } ;
typedef  scalar_t__* PWCHAR ;
typedef  TYPE_2__* PINICACHESECTION ;
typedef  TYPE_1__* PINICACHEKEY ;
typedef  scalar_t__ INSERTION_TYPE ;
typedef  int /*<<< orphan*/  INICACHEKEY ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ INSERT_AFTER ; 
 scalar_t__ INSERT_BEFORE ; 
 scalar_t__ INSERT_FIRST ; 
 scalar_t__ INSERT_LAST ; 
 int /*<<< orphan*/  ProcessHeap ; 
 scalar_t__ RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  wcscpy (TYPE_1__*,scalar_t__*) ; 
 int wcslen (scalar_t__*) ; 

PINICACHEKEY
IniCacheInsertKey(
    PINICACHESECTION Section,
    PINICACHEKEY AnchorKey,
    INSERTION_TYPE InsertionType,
    PWCHAR Name,
    PWCHAR Data)
{
    PINICACHEKEY Key;

    Key = NULL;

    if (Section == NULL ||
        Name == NULL ||
        *Name == 0 ||
        Data == NULL ||
        *Data == 0)
    {
        DPRINT("Invalid parameter\n");
        return NULL;
    }

    /* Allocate key buffer */
    Key = (PINICACHEKEY)RtlAllocateHeap(ProcessHeap,
                                        HEAP_ZERO_MEMORY,
                                        sizeof(INICACHEKEY));
    if (Key == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        return NULL;
    }

    /* Allocate name buffer */
    Key->Name = (WCHAR*)RtlAllocateHeap(ProcessHeap,
                                        0,
                                        (wcslen(Name) + 1) * sizeof(WCHAR));
    if (Key->Name == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        RtlFreeHeap(ProcessHeap, 0, Key);
        return NULL;
    }

    /* Copy value name */
    wcscpy(Key->Name, Name);

    /* Allocate data buffer */
    Key->Data = (WCHAR*)RtlAllocateHeap(ProcessHeap,
                                        0,
                                        (wcslen(Data) + 1) * sizeof(WCHAR));
    if (Key->Data == NULL)
    {
        DPRINT("RtlAllocateHeap() failed\n");
        RtlFreeHeap(ProcessHeap, 0, Key->Name);
        RtlFreeHeap(ProcessHeap, 0, Key);
        return NULL;
    }

    /* Copy value data */
    wcscpy(Key->Data, Data);

    /* Insert key into section */
    if (Section->FirstKey == NULL)
    {
        Section->FirstKey = Key;
        Section->LastKey = Key;
    }
    else if ((InsertionType == INSERT_FIRST) ||
             ((InsertionType == INSERT_BEFORE) && ((AnchorKey == NULL) || (AnchorKey == Section->FirstKey))))
    {
        /* Insert at the head of the list */
        Section->FirstKey->Prev = Key;
        Key->Next = Section->FirstKey;
        Section->FirstKey = Key;
    }
    else if ((InsertionType == INSERT_BEFORE) && (AnchorKey != NULL))
    {
        /* Insert before the anchor key */
        Key->Next = AnchorKey;
        Key->Prev = AnchorKey->Prev;
        AnchorKey->Prev->Next = Key;
        AnchorKey->Prev = Key;
    }
    else if ((InsertionType == INSERT_LAST) ||
             ((InsertionType == INSERT_AFTER) && ((AnchorKey == NULL) || (AnchorKey == Section->LastKey))))
    {
        Section->LastKey->Next = Key;
        Key->Prev = Section->LastKey;
        Section->LastKey = Key;
    }
    else if ((InsertionType == INSERT_AFTER) && (AnchorKey != NULL))
    {
        /* Insert after the anchor key */
        Key->Next = AnchorKey->Next;
        Key->Prev = AnchorKey;
        AnchorKey->Next->Prev = Key;
        AnchorKey->Next = Key;
    }

    return Key;
}