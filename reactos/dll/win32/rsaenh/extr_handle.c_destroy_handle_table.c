#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* DebugInfo; } ;
struct handle_table {TYPE_2__ mutex; int /*<<< orphan*/  paEntries; } ;
struct TYPE_3__ {scalar_t__* Spare; } ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_2__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct handle_table*) ; 

void destroy_handle_table(struct handle_table *lpTable)
{
    TRACE("(lpTable=%p)\n", lpTable);
        
    HeapFree(GetProcessHeap(), 0, lpTable->paEntries);
    lpTable->mutex.DebugInfo->Spare[0] = 0;
    DeleteCriticalSection(&lpTable->mutex);
}