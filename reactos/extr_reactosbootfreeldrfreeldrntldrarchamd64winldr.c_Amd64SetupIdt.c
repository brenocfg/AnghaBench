#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_2__ {int Limit; int /*<<< orphan*/  Base; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  KIDTENTRY ;
typedef  TYPE_1__ KDESCRIPTOR ;

/* Variables and functions */
 int NUM_IDT ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  __lidt (int*) ; 
 int /*<<< orphan*/  __sidt (int*) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static
VOID
Amd64SetupIdt(PVOID IdtBase)
{
    KDESCRIPTOR IdtDesc, OldIdt;
    ULONG Size;
    TRACE("Amd64SetupIdt(IdtBase = %p)\n", IdtBase);

    /* Get old IDT */
    __sidt(&OldIdt.Limit);

    /* Copy the old IDT */
    Size =  min(OldIdt.Limit + 1, NUM_IDT * sizeof(KIDTENTRY));
    //RtlCopyMemory(IdtBase, (PVOID)OldIdt.Base, Size);

    /* Setup the new IDT descriptor */
    IdtDesc.Base = IdtBase;
    IdtDesc.Limit = NUM_IDT * sizeof(KIDTENTRY) - 1;

    /* Set the new IDT */
    __lidt(&IdtDesc.Limit);
    TRACE("Leave Amd64SetupIdt()\n");
}