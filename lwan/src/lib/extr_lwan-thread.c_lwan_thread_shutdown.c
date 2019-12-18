#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lwan_thread {int /*<<< orphan*/  wheel; int /*<<< orphan*/  pending_fds; int /*<<< orphan*/  self; int /*<<< orphan*/ * pipe_fd; int /*<<< orphan*/  epoll_fd; } ;
struct TYPE_2__ {int count; struct lwan_thread* threads; int /*<<< orphan*/  barrier; } ;
struct lwan {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct lwan_thread*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 int /*<<< orphan*/  lwan_thread_nudge (struct lwan_thread*) ; 
 int /*<<< orphan*/  pthread_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spsc_queue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timeouts_close (int /*<<< orphan*/ ) ; 

void lwan_thread_shutdown(struct lwan *l)
{
    lwan_status_debug("Shutting down threads");

    for (int i = 0; i < l->thread.count; i++) {
        struct lwan_thread *t = &l->thread.threads[i];

        close(t->epoll_fd);
        lwan_thread_nudge(t);
    }

    pthread_barrier_wait(&l->thread.barrier);
    pthread_barrier_destroy(&l->thread.barrier);

    for (int i = 0; i < l->thread.count; i++) {
        struct lwan_thread *t = &l->thread.threads[i];

        close(t->pipe_fd[0]);
#if !defined(HAVE_EVENTFD)
        close(t->pipe_fd[1]);
#endif

        pthread_join(l->thread.threads[i].self, NULL);
        spsc_queue_free(&t->pending_fds);
        timeouts_close(t->wheel);
    }

    free(l->thread.threads);
}