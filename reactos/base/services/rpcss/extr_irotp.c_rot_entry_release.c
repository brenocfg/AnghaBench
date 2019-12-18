#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rot_entry {struct rot_entry* moniker_data; struct rot_entry* moniker; struct rot_entry* object; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rot_entry*) ; 
 int /*<<< orphan*/  InterlockedDecrement (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rot_entry_release(struct rot_entry *rot_entry)
{
    if (!InterlockedDecrement(&rot_entry->refs))
    {
        HeapFree(GetProcessHeap(), 0, rot_entry->object);
        HeapFree(GetProcessHeap(), 0, rot_entry->moniker);
        HeapFree(GetProcessHeap(), 0, rot_entry->moniker_data);
        HeapFree(GetProcessHeap(), 0, rot_entry);
    }
}