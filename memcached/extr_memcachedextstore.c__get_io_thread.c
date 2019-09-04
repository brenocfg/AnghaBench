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
struct TYPE_5__ {long long depth; } ;
typedef  TYPE_1__ store_io_thread ;
struct TYPE_6__ {int io_threadcount; TYPE_1__* io_threads; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ store_engine ;

/* Variables and functions */
 long long LLONG_MAX ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static store_io_thread *_get_io_thread(store_engine *e) {
    int tid = -1;
    long long int low = LLONG_MAX;
    pthread_mutex_lock(&e->mutex);
    // find smallest queue. ignoring lock since being wrong isn't fatal.
    // TODO: if average queue depth can be quickly tracked, can break as soon
    // as we see a thread that's less than average, and start from last_io_thread
    for (int x = 0; x < e->io_threadcount; x++) {
        if (e->io_threads[x].depth == 0) {
            tid = x;
            break;
        } else if (e->io_threads[x].depth < low) {
                tid = x;
            low = e->io_threads[x].depth;
        }
    }
    pthread_mutex_unlock(&e->mutex);

    return &e->io_threads[tid];
}