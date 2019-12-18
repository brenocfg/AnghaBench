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
typedef  int uint32_t ;
struct lwan_thread {int dummy; } ;
struct lwan_connection {int dummy; } ;
struct TYPE_4__ {short count; unsigned int max_fd; int /*<<< orphan*/  barrier; int /*<<< orphan*/ * threads; } ;
struct lwan {TYPE_2__ thread; TYPE_1__* conns; } ;
struct TYPE_3__ {int /*<<< orphan*/ * thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_threads_affinity (struct lwan*,int*,int) ; 
 int* alloca (int) ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 
 int /*<<< orphan*/  create_thread (struct lwan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lwan_nextpow2 (size_t) ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  lwan_status_debug (char*) ; 
 scalar_t__ pthread_barrier_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 int /*<<< orphan*/  topology_to_schedtbl (struct lwan*,int*,int) ; 

void lwan_thread_init(struct lwan *l)
{
    if (pthread_barrier_init(&l->thread.barrier, NULL,
                             (unsigned)l->thread.count + 1))
        lwan_status_critical("Could not create barrier");

    lwan_status_debug("Initializing threads");

    l->thread.threads =
        calloc((size_t)l->thread.count, sizeof(struct lwan_thread));
    if (!l->thread.threads)
        lwan_status_critical("Could not allocate memory for threads");

    for (short i = 0; i < l->thread.count; i++)
        create_thread(l, &l->thread.threads[i]);

    const unsigned int total_conns = l->thread.max_fd * l->thread.count;
#ifdef __x86_64__
    static_assert(sizeof(struct lwan_connection) == 32,
                  "Two connections per cache line");
    /*
     * Pre-schedule each file descriptor, to reduce some operations in the
     * fast path.
     *
     * Since struct lwan_connection is guaranteed to be 32-byte long, two of
     * them can fill up a cache line.  Assume siblings share cache lines and
     * use the CPU topology to group two connections per cache line in such
     * a way that false sharing is avoided.
     */
    uint32_t n_threads = (uint32_t)lwan_nextpow2((size_t)((l->thread.count - 1) * 2));
    uint32_t *schedtbl = alloca(n_threads * sizeof(uint32_t));

    topology_to_schedtbl(l, schedtbl, n_threads);

    n_threads--; /* Transform count into mask for AND below */
    adjust_threads_affinity(l, schedtbl, n_threads);
    for (unsigned int i = 0; i < total_conns; i++)
        l->conns[i].thread = &l->thread.threads[schedtbl[i & n_threads]];
#else
    for (unsigned int i = 0; i < total_conns; i++)
        l->conns[i].thread = &l->thread.threads[i % l->thread.count];
#endif

    pthread_barrier_wait(&l->thread.barrier);

    lwan_status_debug("Worker threads created and ready to serve");
}