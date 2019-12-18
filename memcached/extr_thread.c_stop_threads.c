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
struct TYPE_4__ {scalar_t__ verbose; int num_threads; } ;
struct TYPE_3__ {int /*<<< orphan*/  notify_send_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAWLER_WAIT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ init_count ; 
 int /*<<< orphan*/  init_lock ; 
 int /*<<< orphan*/  logger_stop () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stop_assoc_maintenance_thread () ; 
 int /*<<< orphan*/  stop_conn_timeout_thread () ; 
 int /*<<< orphan*/  stop_item_crawler_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_lru_maintainer_thread () ; 
 int /*<<< orphan*/  stop_slab_maintenance_thread () ; 
 TYPE_1__* threads ; 
 int /*<<< orphan*/  wait_for_thread_registration (int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

void stop_threads(void) {
    char buf[1];
    int i;

    // assoc can call pause_threads(), so we have to stop it first.
    stop_assoc_maintenance_thread();
    if (settings.verbose > 0)
        fprintf(stderr, "stopped assoc\n");

    if (settings.verbose > 0)
        fprintf(stderr, "asking workers to stop\n");
    buf[0] = 's';
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

    if (settings.verbose > 0)
        fprintf(stderr, "asking background threads to stop\n");

    // stop each side thread.
    // TODO: Verify these all work if the threads are already stopped
    stop_item_crawler_thread(CRAWLER_WAIT);
    if (settings.verbose > 0)
        fprintf(stderr, "stopped lru crawler\n");
    stop_lru_maintainer_thread();
    if (settings.verbose > 0)
        fprintf(stderr, "stopped maintainer\n");
    stop_slab_maintenance_thread();
    if (settings.verbose > 0)
        fprintf(stderr, "stopped slab mover\n");
    logger_stop();
    if (settings.verbose > 0)
        fprintf(stderr, "stopped logger thread\n");
    stop_conn_timeout_thread();
    if (settings.verbose > 0)
        fprintf(stderr, "stopped idle timeout thread\n");

    if (settings.verbose > 0)
        fprintf(stderr, "all background threads stopped\n");

    // At this point, every background thread must be stopped.
}