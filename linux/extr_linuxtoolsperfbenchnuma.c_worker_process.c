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
typedef  int /*<<< orphan*/  u8 ;
struct thread_data {int process_nr; int thread_nr; int task_nr; int curr_cpu; int /*<<< orphan*/ * process_lock; int /*<<< orphan*/  val; int /*<<< orphan*/ * process_data; int /*<<< orphan*/  bind_cpumask; int /*<<< orphan*/  bind_node; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;
struct TYPE_3__ {int nr_threads; int show_details; int /*<<< orphan*/  bytes_process; } ;
struct TYPE_4__ {TYPE_1__ p; struct thread_data* threads; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bind_to_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bind_to_memnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct thread_data*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  set_taskname (char*,int) ; 
 int /*<<< orphan*/ * setup_private_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_thread ; 
 int /*<<< orphan*/ * zalloc (int) ; 

__attribute__((used)) static void worker_process(int process_nr)
{
	pthread_mutex_t process_lock;
	struct thread_data *td;
	pthread_t *pthreads;
	u8 *process_data;
	int task_nr;
	int ret;
	int t;

	pthread_mutex_init(&process_lock, NULL);
	set_taskname("process %d", process_nr);

	/*
	 * Pick up the memory policy and the CPU binding of our first thread,
	 * so that we initialize memory accordingly:
	 */
	task_nr = process_nr*g->p.nr_threads;
	td = g->threads + task_nr;

	bind_to_memnode(td->bind_node);
	bind_to_cpumask(td->bind_cpumask);

	pthreads = zalloc(g->p.nr_threads * sizeof(pthread_t));
	process_data = setup_private_data(g->p.bytes_process);

	if (g->p.show_details >= 3) {
		printf(" # process %2d global mem: %p, process mem: %p\n",
			process_nr, g->data, process_data);
	}

	for (t = 0; t < g->p.nr_threads; t++) {
		task_nr = process_nr*g->p.nr_threads + t;
		td = g->threads + task_nr;

		td->process_data = process_data;
		td->process_nr   = process_nr;
		td->thread_nr    = t;
		td->task_nr	 = task_nr;
		td->val          = rand();
		td->curr_cpu	 = -1;
		td->process_lock = &process_lock;

		ret = pthread_create(pthreads + t, NULL, worker_thread, td);
		BUG_ON(ret);
	}

	for (t = 0; t < g->p.nr_threads; t++) {
                ret = pthread_join(pthreads[t], NULL);
		BUG_ON(ret);
	}

	free_data(process_data, g->p.bytes_process);
	free(pthreads);
}