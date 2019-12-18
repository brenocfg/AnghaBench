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
struct gc_entry {struct gc_entry* next; } ;
struct gc_arena {struct gc_entry* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct gc_entry*) ; 

void
x_gc_free(struct gc_arena *a)
{
    struct gc_entry *e;
    e = a->list;
    a->list = NULL;

    while (e != NULL)
    {
        struct gc_entry *next = e->next;
        free(e);
        e = next;
    }
}