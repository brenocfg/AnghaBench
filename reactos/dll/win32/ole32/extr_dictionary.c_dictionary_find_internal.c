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
struct dictionary_entry {struct dictionary_entry* next; int /*<<< orphan*/  key; } ;
struct dictionary {scalar_t__ (* comp ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  extra; struct dictionary_entry* head; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct dictionary*) ; 
 scalar_t__ stub1 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dictionary_entry **dictionary_find_internal(struct dictionary *d,
 const void *k)
{
    struct dictionary_entry **ret = NULL;
    struct dictionary_entry *p;

    assert(d);
    /* special case for head containing the desired element */
    if (d->head && d->comp(k, d->head->key, d->extra) == 0)
        ret = &d->head;
    for (p = d->head; !ret && p && p->next; p = p->next)
    {
        if (d->comp(k, p->next->key, d->extra) == 0)
            ret = &p->next;
    }
    return ret;
}