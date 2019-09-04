#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {struct TYPE_8__* Next; int /*<<< orphan*/ * Key; } ;
struct TYPE_7__ {TYPE_3__* FirstLine; } ;
struct TYPE_6__ {scalar_t__ Line; int /*<<< orphan*/ * Section; int /*<<< orphan*/ * Inf; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHESECTION ;
typedef  TYPE_3__* PINFCACHELINE ;
typedef  scalar_t__* PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _stricmp (int /*<<< orphan*/ *,scalar_t__*) ; 

BOOLEAN
InfFindFirstMatchLine (
    PINFCONTEXT ContextIn,
    PCHAR Key,
    PINFCONTEXT ContextOut)
{
    PINFCACHELINE CacheLine;

    if ((ContextIn == NULL) || (ContextOut == NULL) || (Key == NULL) || (*Key == 0))
        return FALSE;

    if (ContextIn->Inf == NULL || ContextIn->Section == NULL)
        return FALSE;

    CacheLine = ((PINFCACHESECTION)(ContextIn->Section))->FirstLine;
    while (CacheLine != NULL)
    {
        if ((CacheLine->Key != NULL) && (_stricmp(CacheLine->Key, Key) == 0))
        {

            if (ContextIn != ContextOut)
            {
                ContextOut->Inf = ContextIn->Inf;
                ContextOut->Section = ContextIn->Section;
            }
            ContextOut->Line = (PVOID)CacheLine;

            return TRUE;
        }

        CacheLine = CacheLine->Next;
    }

    return FALSE;
}