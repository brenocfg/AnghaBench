#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ hWnd; } ;
struct TYPE_7__ {struct TYPE_7__* Flink; } ;
typedef  TYPE_1__* PLIST_ENTRY ;
typedef  TYPE_2__* PDIALOG_LIST_ENTRY ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 TYPE_2__* CONTAINING_RECORD (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIALOG_LIST_ENTRY ; 
 TYPE_1__ DialogListHead ; 
 int /*<<< orphan*/  Entry ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static
PDIALOG_LIST_ENTRY
GetDialogListEntry(HWND hwndDlg)
{
    PDIALOG_LIST_ENTRY Current;
    PLIST_ENTRY ListEntry;

    ListEntry = DialogListHead.Flink;
    while (ListEntry != &DialogListHead)
    {
        Current = CONTAINING_RECORD(ListEntry,
                                    DIALOG_LIST_ENTRY,
                                    Entry);
        if (Current->hWnd == hwndDlg)
        {
            TRACE("Found entry: %p\n", Current);
            return Current;
        }

        ListEntry = ListEntry->Flink;
    }

    TRACE("Found no entry!\n");
    return NULL;
}