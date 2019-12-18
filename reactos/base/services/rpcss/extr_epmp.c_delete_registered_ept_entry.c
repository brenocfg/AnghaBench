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
struct registered_ept_entry {int /*<<< orphan*/  entry; int /*<<< orphan*/  address; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  protseq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct registered_ept_entry*) ; 
 int /*<<< orphan*/  I_RpcFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delete_registered_ept_entry(struct registered_ept_entry *entry)
{
    I_RpcFree(entry->protseq);
    I_RpcFree(entry->endpoint);
    I_RpcFree(entry->address);
    list_remove(&entry->entry);
    HeapFree(GetProcessHeap(), 0, entry);
}