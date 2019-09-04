#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {int /*<<< orphan*/  Entry; } ;
typedef  TYPE_1__* PDIALOG_LIST_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  RemoveEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static
VOID
RemoveDialogListEntry(PDIALOG_LIST_ENTRY ListEntry)
{
    TRACE("Remove entry %p\n", ListEntry);

    RemoveEntryList(&ListEntry->Entry);
    RtlFreeHeap(RtlGetProcessHeap(), 0, ListEntry);
}