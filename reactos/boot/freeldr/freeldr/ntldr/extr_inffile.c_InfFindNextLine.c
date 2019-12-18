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
struct TYPE_6__ {int /*<<< orphan*/ * Next; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Line; int /*<<< orphan*/  Section; int /*<<< orphan*/  Inf; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PINFCONTEXT ;
typedef  TYPE_2__* PINFCACHELINE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
InfFindNextLine (
    PINFCONTEXT ContextIn,
    PINFCONTEXT ContextOut)
{
    PINFCACHELINE CacheLine;

    if ((ContextIn == NULL) || (ContextOut == NULL))
        return FALSE;

    if (ContextIn->Line == NULL)
        return FALSE;

    CacheLine = (PINFCACHELINE)ContextIn->Line;
    if (CacheLine->Next == NULL)
        return FALSE;

    if (ContextIn != ContextOut)
    {
        ContextOut->Inf = ContextIn->Inf;
        ContextOut->Section = ContextIn->Section;
    }
    ContextOut->Line = (PVOID)(CacheLine->Next);

    return TRUE;
}