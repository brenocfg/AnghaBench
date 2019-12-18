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
typedef  scalar_t__ ULONG ;
struct TYPE_7__ {struct TYPE_7__* Next; int /*<<< orphan*/  Data; } ;
struct TYPE_6__ {scalar_t__ FieldCount; TYPE_3__* FirstField; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Line; } ;
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  TYPE_3__* PINFCACHEFIELD ;
typedef  scalar_t__* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcpy (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

BOOLEAN
InfGetMultiSzField (
    PINFCONTEXT Context,
    ULONG FieldIndex,
    PCHAR ReturnBuffer,
    ULONG ReturnBufferSize,
    PULONG RequiredSize)
{
    PINFCACHELINE CacheLine;
    PINFCACHEFIELD CacheField;
    PINFCACHEFIELD FieldPtr;
    ULONG Index;
    SIZE_T Size;
    PCHAR Ptr;

    if ((Context == NULL) || (Context->Line == NULL) || (FieldIndex == 0))
    {
//      DPRINT("Invalid parameter\n");
        return FALSE;
    }

    if (RequiredSize != NULL)
        *RequiredSize = 0;

    CacheLine = (PINFCACHELINE)Context->Line;

    if (FieldIndex > CacheLine->FieldCount)
        return FALSE;

    CacheField = CacheLine->FirstField;
    for (Index = 1; Index < FieldIndex; Index++)
        CacheField = CacheField->Next;

    /* Calculate the required buffer size */
    FieldPtr = CacheField;
    Size = 0;
    while (FieldPtr != NULL)
    {
        Size += (strlen(FieldPtr->Data) + 1);
        FieldPtr = FieldPtr->Next;
    }
    Size++;

    if (RequiredSize != NULL)
        *RequiredSize = (ULONG)Size;

    if (ReturnBuffer != NULL)
    {
        if (ReturnBufferSize < Size)
            return FALSE;

        /* Copy multi-sz string */
        Ptr = ReturnBuffer;
        FieldPtr = CacheField;
        while (FieldPtr != NULL)
        {
            Size = strlen(FieldPtr->Data) + 1;

            strcpy(Ptr, FieldPtr->Data);

            Ptr = Ptr + Size;
            FieldPtr = FieldPtr->Next;
        }
        *Ptr = 0;
    }

    return TRUE;
}