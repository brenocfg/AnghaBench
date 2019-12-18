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
struct stub_manager {int /*<<< orphan*/  entry; scalar_t__ refs; TYPE_1__* apt; } ;
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  cs; } ;
typedef  TYPE_1__ APARTMENT ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_manager_delete (struct stub_manager*) ; 

ULONG stub_manager_int_release(struct stub_manager *This)
{
    ULONG refs;
    APARTMENT *apt = This->apt;

    EnterCriticalSection(&apt->cs);
    refs = --This->refs;

    TRACE("after %d\n", refs);

    /* remove from apartment so no other thread can access it... */
    if (!refs)
        list_remove(&This->entry);

    LeaveCriticalSection(&apt->cs);

    /* ... so now we can delete it without being inside the apartment critsec */
    if (!refs)
        stub_manager_delete(This);

    return refs;
}