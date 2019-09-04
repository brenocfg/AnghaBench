#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hv; int /*<<< orphan*/  it; } ;
typedef  TYPE_1__ lru_bump_entry ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  buf; struct TYPE_5__* next; } ;
typedef  TYPE_2__ lru_bump_buf ;

/* Variables and functions */
 scalar_t__ bipbuf_peek_all (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ bipbuf_poll (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* bump_buf_head ; 
 int /*<<< orphan*/  bump_buf_lock ; 
 int /*<<< orphan*/  do_item_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_item_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool lru_maintainer_bumps(void) {
    lru_bump_buf *b;
    lru_bump_entry *be;
    unsigned int size;
    unsigned int todo;
    bool bumped = false;
    pthread_mutex_lock(&bump_buf_lock);
    for (b = bump_buf_head; b != NULL; b=b->next) {
        pthread_mutex_lock(&b->mutex);
        be = (lru_bump_entry *) bipbuf_peek_all(b->buf, &size);
        pthread_mutex_unlock(&b->mutex);

        if (be == NULL) {
            continue;
        }
        todo = size;
        bumped = true;

        while (todo) {
            item_lock(be->hv);
            do_item_update(be->it);
            do_item_remove(be->it);
            item_unlock(be->hv);
            be++;
            todo -= sizeof(lru_bump_entry);
        }

        pthread_mutex_lock(&b->mutex);
        be = (lru_bump_entry *) bipbuf_poll(b->buf, size);
        pthread_mutex_unlock(&b->mutex);
    }
    pthread_mutex_unlock(&bump_buf_lock);
    return bumped;
}