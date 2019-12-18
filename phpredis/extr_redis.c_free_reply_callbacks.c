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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ fold_item ;
struct TYPE_6__ {int /*<<< orphan*/ * current; TYPE_1__* head; } ;
typedef  TYPE_2__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void
free_reply_callbacks(RedisSock *redis_sock)
{
    fold_item *fi;

    for (fi = redis_sock->head; fi; ) {
        fold_item *fi_next = fi->next;
        free(fi);
        fi = fi_next;
    }
    redis_sock->head = NULL;
    redis_sock->current = NULL;
}