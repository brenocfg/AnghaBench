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
struct gc_entry_special {void (* free_fnc ) (void*) ;struct gc_entry_special* next; void* addr; } ;
struct gc_arena {struct gc_entry_special* list_special; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct gc_arena*) ; 
 int /*<<< orphan*/  check_malloc_return (struct gc_entry_special*) ; 
 int /*<<< orphan*/  file ; 
 int /*<<< orphan*/  line ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ openvpn_dmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
gc_addspecial(void *addr, void (free_function)(void *), struct gc_arena *a)
{
    ASSERT(a);
    struct gc_entry_special *e;
#ifdef DMALLOC
    e = (struct gc_entry_special *) openvpn_dmalloc(file, line, sizeof(struct gc_entry_special));
#else
    e = (struct gc_entry_special *) malloc(sizeof(struct gc_entry_special));
#endif
    check_malloc_return(e);
    e->free_fnc = free_function;
    e->addr = addr;

    e->next = a->list_special;
    a->list_special = e;
}