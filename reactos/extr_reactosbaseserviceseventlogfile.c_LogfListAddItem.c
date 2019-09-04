#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int /*<<< orphan*/  ListEntry; } ;
typedef  TYPE_1__* PLOGFILE ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LogFileListCs ; 
 int /*<<< orphan*/  LogFileListHead ; 

__attribute__((used)) static VOID
LogfListAddItem(PLOGFILE Item)
{
    EnterCriticalSection(&LogFileListCs);
    InsertTailList(&LogFileListHead, &Item->ListEntry);
    LeaveCriticalSection(&LogFileListCs);
}