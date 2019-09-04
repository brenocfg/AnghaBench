#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_7__ {int /*<<< orphan*/  Data; struct TYPE_7__* Next; } ;
struct TYPE_6__ {int FieldCount; TYPE_3__* FirstField; int /*<<< orphan*/  Key; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Line; } ;
typedef  int /*<<< orphan*/ * PLONG ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  TYPE_3__* PINFCACHEFIELD ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 

BOOLEAN
InfGetIntField (
    PINFCONTEXT Context,
    ULONG FieldIndex,
    PLONG IntegerValue)
{
    PINFCACHELINE CacheLine;
    PINFCACHEFIELD CacheField;
    ULONG Index;
    PCHAR Ptr;

    if ((Context == NULL) || (Context->Line == NULL) || (IntegerValue == NULL))
    {
//      DPRINT("Invalid parameter\n");
        return FALSE;
    }

    CacheLine = (PINFCACHELINE)Context->Line;

    if (FieldIndex > CacheLine->FieldCount)
    {
//      DPRINT("Invalid parameter\n");
        return FALSE;
    }

    if (FieldIndex == 0)
    {
        Ptr = CacheLine->Key;
    }
    else
    {
        CacheField = CacheLine->FirstField;
        for (Index = 1; Index < FieldIndex; Index++)
            CacheField = CacheField->Next;

        Ptr = CacheField->Data;
    }

    *IntegerValue = atoi(Ptr); //strtol(Ptr, NULL, 0);

    return TRUE;
}