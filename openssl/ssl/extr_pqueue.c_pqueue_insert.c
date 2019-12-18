#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* items; } ;
typedef  TYPE_1__ pqueue ;
struct TYPE_7__ {struct TYPE_7__* next; int /*<<< orphan*/  priority; } ;
typedef  TYPE_2__ pitem ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

pitem *pqueue_insert(pqueue *pq, pitem *item)
{
    pitem *curr, *next;

    if (pq->items == NULL) {
        pq->items = item;
        return item;
    }

    for (curr = NULL, next = pq->items;
         next != NULL; curr = next, next = next->next) {
        /*
         * we can compare 64-bit value in big-endian encoding with memcmp:-)
         */
        int cmp = memcmp(next->priority, item->priority, 8);
        if (cmp > 0) {          /* next > item */
            item->next = next;

            if (curr == NULL)
                pq->items = item;
            else
                curr->next = item;

            return item;
        }

        else if (cmp == 0)      /* duplicates not allowed */
            return NULL;
    }

    item->next = NULL;
    curr->next = item;

    return item;
}