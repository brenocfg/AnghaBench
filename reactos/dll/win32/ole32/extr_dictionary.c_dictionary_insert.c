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
struct dictionary_entry {struct dictionary_entry* next; void* value; void* key; } ;
struct dictionary {int /*<<< orphan*/  num_entries; struct dictionary_entry* head; int /*<<< orphan*/  extra; int /*<<< orphan*/  (* destroy ) (void*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct dictionary_entry* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,struct dictionary*,void const*,void const*) ; 
 struct dictionary_entry** dictionary_find_internal (struct dictionary*,void const*) ; 
 int /*<<< orphan*/  stub1 (void*,void*,int /*<<< orphan*/ ) ; 

void dictionary_insert(struct dictionary *d, const void *k, const void *v)
{
    struct dictionary_entry **prior;

    TRACE("(%p, %p, %p)\n", d, k, v);
    if (!d)
        return;
    if ((prior = dictionary_find_internal(d, k)))
    {
        if (d->destroy)
            d->destroy((*prior)->key, (*prior)->value, d->extra);
        (*prior)->key = (void *)k;
        (*prior)->value = (void *)v;
    }
    else
    {
        struct dictionary_entry *elem = HeapAlloc(GetProcessHeap(), 0,
                                            sizeof(struct dictionary_entry));

        if (!elem)
            return;
        elem->key = (void *)k;
        elem->value = (void *)v;
        elem->next = d->head;
        d->head = elem;
        d->num_entries++;
    }
}