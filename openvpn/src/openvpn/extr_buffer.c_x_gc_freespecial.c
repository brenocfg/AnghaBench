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
struct gc_entry_special {int /*<<< orphan*/  addr; int /*<<< orphan*/  (* free_fnc ) (int /*<<< orphan*/ ) ;struct gc_entry_special* next; } ;
struct gc_arena {struct gc_entry_special* list_special; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct gc_entry_special*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
x_gc_freespecial(struct gc_arena *a)
{
    struct gc_entry_special *e;
    e = a->list_special;
    a->list_special = NULL;

    while (e != NULL)
    {
        struct gc_entry_special *next = e->next;
        e->free_fnc(e->addr);
        free(e);
        e = next;
    }
}