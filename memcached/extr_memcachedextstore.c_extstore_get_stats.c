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
struct extstore_stats {int pages_free; int pages_used; scalar_t__ bytes_used; scalar_t__ bytes_fragmented; scalar_t__ io_queue; } ;
struct TYPE_6__ {int page_free; int page_count; int io_threadcount; int page_size; TYPE_1__* io_threads; int /*<<< orphan*/  mutex; int /*<<< orphan*/  stats; } ;
typedef  TYPE_2__ store_engine ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_L (TYPE_2__*) ; 
 int /*<<< orphan*/  STAT_UL (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (struct extstore_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void extstore_get_stats(void *ptr, struct extstore_stats *st) {
    store_engine *e = (store_engine *)ptr;
    STAT_L(e);
    memcpy(st, &e->stats, sizeof(struct extstore_stats));
    STAT_UL(e);

    // grab pages_free/pages_used
    pthread_mutex_lock(&e->mutex);
    st->pages_free = e->page_free;
    st->pages_used = e->page_count - e->page_free;
    pthread_mutex_unlock(&e->mutex);
    st->io_queue = 0;
    for (int x = 0; x < e->io_threadcount; x++) {
        pthread_mutex_lock(&e->io_threads[x].mutex);
        st->io_queue += e->io_threads[x].depth;
        pthread_mutex_unlock(&e->io_threads[x].mutex);
    }
    // calculate bytes_fragmented.
    // note that open and yet-filled pages count against fragmentation.
    st->bytes_fragmented = st->pages_used * e->page_size -
        st->bytes_used;
}