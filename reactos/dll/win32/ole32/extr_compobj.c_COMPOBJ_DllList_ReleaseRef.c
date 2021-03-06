#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* library_name; int /*<<< orphan*/  library; int /*<<< orphan*/  entry; int /*<<< orphan*/  refs; } ;
typedef  TYPE_1__ OpenDll ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csOpenDllList ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void COMPOBJ_DllList_ReleaseRef(OpenDll *entry, BOOL free_entry)
{
    if (!InterlockedDecrement(&entry->refs) && free_entry)
    {
        EnterCriticalSection(&csOpenDllList);
        list_remove(&entry->entry);
        LeaveCriticalSection(&csOpenDllList);

        TRACE("freeing %p\n", entry->library);
        FreeLibrary(entry->library);

        HeapFree(GetProcessHeap(), 0, entry->library_name);
        HeapFree(GetProcessHeap(), 0, entry);
    }
}