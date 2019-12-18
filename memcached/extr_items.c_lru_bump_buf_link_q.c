#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* prev; struct TYPE_5__* next; } ;
typedef  TYPE_1__ lru_bump_buf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* bump_buf_head ; 
 int /*<<< orphan*/  bump_buf_lock ; 
 TYPE_1__* bump_buf_tail ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lru_bump_buf_link_q(lru_bump_buf *b) {
    pthread_mutex_lock(&bump_buf_lock);
    assert(b != bump_buf_head);

    b->prev = 0;
    b->next = bump_buf_head;
    if (b->next) b->next->prev = b;
    bump_buf_head = b;
    if (bump_buf_tail == 0) bump_buf_tail = b;
    pthread_mutex_unlock(&bump_buf_lock);
    return;
}