#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timeval {unsigned int tv_usec; } ;
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_mask; } ;
struct perf_cpu_map {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ USEC_PER_MSEC ; 
 int /*<<< orphan*/  bench_futex_wake_usage ; 
 unsigned int bench_repeat ; 
 int /*<<< orphan*/  block_threads (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct perf_cpu_map*) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ fshared ; 
 int /*<<< orphan*/  futex1 ; 
 int /*<<< orphan*/  futex_flag ; 
 scalar_t__ futex_wake (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int ncpus ; 
 int nthreads ; 
 int nwakes ; 
 int /*<<< orphan*/  options ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_summary () ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,...) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  thread_lock ; 
 int /*<<< orphan*/  thread_parent ; 
 int /*<<< orphan*/  thread_worker ; 
 scalar_t__ threads_starting ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  toggle_done ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  waketime_stats ; 
 int /*<<< orphan*/  wakeup_stats ; 
 int /*<<< orphan*/ * worker ; 

int bench_futex_wake(int argc, const char **argv)
{
	int ret = 0;
	unsigned int i, j;
	struct sigaction act;
	pthread_attr_t thread_attr;
	struct perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_wake_usage, 0);
	if (argc) {
		usage_with_options(bench_futex_wake_usage, options);
		exit(EXIT_FAILURE);
	}

	cpu = perf_cpu_map__new(NULL);
	if (!cpu)
		err(EXIT_FAILURE, "calloc");

	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_done;
	sigaction(SIGINT, &act, NULL);

	if (!nthreads)
		nthreads = ncpus;

	worker = calloc(nthreads, sizeof(*worker));
	if (!worker)
		err(EXIT_FAILURE, "calloc");

	if (!fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	printf("Run summary [PID %d]: blocking on %d threads (at [%s] futex %p), "
	       "waking up %d at a time.\n\n",
	       getpid(), nthreads, fshared ? "shared":"private",  &futex1, nwakes);

	init_stats(&wakeup_stats);
	init_stats(&waketime_stats);
	pthread_attr_init(&thread_attr);
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_parent, NULL);
	pthread_cond_init(&thread_worker, NULL);

	for (j = 0; j < bench_repeat && !done; j++) {
		unsigned int nwoken = 0;
		struct timeval start, end, runtime;

		/* create, launch & block all threads */
		block_threads(worker, thread_attr, cpu);

		/* make sure all threads are already blocked */
		pthread_mutex_lock(&thread_lock);
		while (threads_starting)
			pthread_cond_wait(&thread_parent, &thread_lock);
		pthread_cond_broadcast(&thread_worker);
		pthread_mutex_unlock(&thread_lock);

		usleep(100000);

		/* Ok, all threads are patiently blocked, start waking folks up */
		gettimeofday(&start, NULL);
		while (nwoken != nthreads)
			nwoken += futex_wake(&futex1, nwakes, futex_flag);
		gettimeofday(&end, NULL);
		timersub(&end, &start, &runtime);

		update_stats(&wakeup_stats, nwoken);
		update_stats(&waketime_stats, runtime.tv_usec);

		if (!silent) {
			printf("[Run %d]: Wokeup %d of %d threads in %.4f ms\n",
			       j + 1, nwoken, nthreads, runtime.tv_usec / (double)USEC_PER_MSEC);
		}

		for (i = 0; i < nthreads; i++) {
			ret = pthread_join(worker[i], NULL);
			if (ret)
				err(EXIT_FAILURE, "pthread_join");
		}

	}

	/* cleanup & report results */
	pthread_cond_destroy(&thread_parent);
	pthread_cond_destroy(&thread_worker);
	pthread_mutex_destroy(&thread_lock);
	pthread_attr_destroy(&thread_attr);

	print_summary();

	free(worker);
	return ret;
}