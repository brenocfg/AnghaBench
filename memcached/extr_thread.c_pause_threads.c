#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum pause_thread_types { ____Placeholder_pause_thread_types } pause_thread_types ;
struct TYPE_4__ {int num_threads; } ;
struct TYPE_3__ {int /*<<< orphan*/  notify_send_fd; } ;

/* Variables and functions */
#define  PAUSE_ALL_THREADS 131 
#define  PAUSE_WORKER_THREADS 130 
#define  RESUME_ALL_THREADS 129 
#define  RESUME_WORKER_THREADS 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ init_count ; 
 int /*<<< orphan*/  init_lock ; 
 int /*<<< orphan*/  lru_crawler_pause () ; 
 int /*<<< orphan*/  lru_crawler_resume () ; 
 int /*<<< orphan*/  lru_maintainer_pause () ; 
 int /*<<< orphan*/  lru_maintainer_resume () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ settings ; 
 int /*<<< orphan*/  slabs_rebalancer_pause () ; 
 int /*<<< orphan*/  slabs_rebalancer_resume () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  storage_compact_pause () ; 
 int /*<<< orphan*/  storage_compact_resume () ; 
 int /*<<< orphan*/  storage_write_pause () ; 
 int /*<<< orphan*/  storage_write_resume () ; 
 TYPE_1__* threads ; 
 int /*<<< orphan*/  wait_for_thread_registration (int) ; 
 int /*<<< orphan*/  worker_hang_lock ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void pause_threads(enum pause_thread_types type) {
    char buf[1];
    int i;

    buf[0] = 0;
    switch (type) {
        case PAUSE_ALL_THREADS:
            slabs_rebalancer_pause();
            lru_maintainer_pause();
            lru_crawler_pause();
#ifdef EXTSTORE
            storage_compact_pause();
            storage_write_pause();
#endif
        case PAUSE_WORKER_THREADS:
            buf[0] = 'p';
            pthread_mutex_lock(&worker_hang_lock);
            break;
        case RESUME_ALL_THREADS:
            slabs_rebalancer_resume();
            lru_maintainer_resume();
            lru_crawler_resume();
#ifdef EXTSTORE
            storage_compact_resume();
            storage_write_resume();
#endif
        case RESUME_WORKER_THREADS:
            pthread_mutex_unlock(&worker_hang_lock);
            break;
        default:
            fprintf(stderr, "Unknown lock type: %d\n", type);
            assert(1 == 0);
            break;
    }

    /* Only send a message if we have one. */
    if (buf[0] == 0) {
        return;
    }

    pthread_mutex_lock(&init_lock);
    init_count = 0;
    for (i = 0; i < settings.num_threads; i++) {
        if (write(threads[i].notify_send_fd, buf, 1) != 1) {
            perror("Failed writing to notify pipe");
            /* TODO: This is a fatal problem. Can it ever happen temporarily? */
        }
    }
    wait_for_thread_registration(settings.num_threads);
    pthread_mutex_unlock(&init_lock);
}