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
struct dictionary_entry {int /*<<< orphan*/  extra; int /*<<< orphan*/  value; int /*<<< orphan*/  key; int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct dictionary_entry* next; struct dictionary_entry* head; } ;
struct dictionary {int /*<<< orphan*/  extra; int /*<<< orphan*/  value; int /*<<< orphan*/  key; int /*<<< orphan*/  (* destroy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct dictionary* next; struct dictionary* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dictionary_entry*) ; 
 int /*<<< orphan*/  TRACE (char*,struct dictionary_entry*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dictionary_destroy(struct dictionary *d)
{
    TRACE("(%p)\n", d);
    if (d)
    {
        struct dictionary_entry *p;

        for (p = d->head; p; )
        {
            struct dictionary_entry *next = p->next;

            if (d->destroy)
                d->destroy(p->key, p->value, d->extra);
            HeapFree(GetProcessHeap(), 0, p);
            p = next;
        }
        HeapFree(GetProcessHeap(), 0, d);
    }
}