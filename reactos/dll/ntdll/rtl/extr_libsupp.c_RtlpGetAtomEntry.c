#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {int /*<<< orphan*/ * AtomEntry; } ;
struct TYPE_4__ {int /*<<< orphan*/  RtlHandleTable; } ;
typedef  int /*<<< orphan*/  PRTL_HANDLE_TABLE_ENTRY ;
typedef  int /*<<< orphan*/ * PRTL_ATOM_TABLE_ENTRY ;
typedef  TYPE_1__* PRTL_ATOM_TABLE ;
typedef  TYPE_2__* PRTL_ATOM_HANDLE ;

/* Variables and functions */
 scalar_t__ RtlIsValidIndexHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

PRTL_ATOM_TABLE_ENTRY
RtlpGetAtomEntry(PRTL_ATOM_TABLE AtomTable, ULONG Index)
{
   PRTL_HANDLE_TABLE_ENTRY RtlHandle;

   if (RtlIsValidIndexHandle(&AtomTable->RtlHandleTable,
                             Index,
                             &RtlHandle))
   {
      PRTL_ATOM_HANDLE AtomHandle = (PRTL_ATOM_HANDLE)RtlHandle;

      return AtomHandle->AtomEntry;
   }

   return NULL;
}