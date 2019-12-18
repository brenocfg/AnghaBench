#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* items; } ;
typedef  TYPE_1__ pqueue ;
struct TYPE_6__ {int /*<<< orphan*/  priority; struct TYPE_6__* next; } ;
typedef  TYPE_2__ pitem ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,unsigned char*,int) ; 

pitem *pqueue_find(pqueue *pq, unsigned char *prio64be)
{
    pitem *next;
    pitem *found = NULL;

    if (pq->items == NULL)
        return NULL;

    for (next = pq->items; next->next != NULL; next = next->next) {
        if (memcmp(next->priority, prio64be, 8) == 0) {
            found = next;
            break;
        }
    }

    /* check the one last node */
    if (memcmp(next->priority, prio64be, 8) == 0)
        found = next;

    if (!found)
        return NULL;

    return found;
}