#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  (* sa_sigaction ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  sa_mask; } ;
struct perf_cpu_map {int nr; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_7__ {unsigned long tv_sec; } ;
struct TYPE_6__ {unsigned long ops; int tid; int futex; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  bench_futex_lock_pi_usage ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  create_threads (TYPE_1__*,int /*<<< orphan*/ ,struct perf_cpu_map*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  fshared ; 
 int /*<<< orphan*/  futex_flag ; 
 int getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 scalar_t__ multi ; 
 int nsecs ; 
 int nthreads ; 
 int /*<<< orphan*/  options ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct perf_cpu_map* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_summary () ; 
 int /*<<< orphan*/  printf (char*,int,int,unsigned long) ; 
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
 TYPE_2__ runtime ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  thread_lock ; 
 int /*<<< orphan*/  thread_parent ; 
 int /*<<< orphan*/  thread_worker ; 
 int threads_starting ; 
 int /*<<< orphan*/  throughput_stats ; 
 int /*<<< orphan*/  toggle_done (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* worker ; 
 int /*<<< orphan*/  zfree (int*) ; 

int bench_futex_lock_pi(int argc, const char **argv)
{
	int ret = 0;
	unsigned int i;
	struct sigaction act;
	pthread_attr_t thread_attr;
	struct perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_lock_pi_usage, 0);
	if (argc)
		goto err;

	cpu = perf_cpu_map__new(NULL);
	if (!cpu)
		err(EXIT_FAILURE, "calloc");

	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_done;
	sigaction(SIGINT, &act, NULL);

	if (!nthreads)
		nthreads = cpu->nr;

	worker = calloc(nthreads, sizeof(*worker));
	if (!worker)
		err(EXIT_FAILURE, "calloc");

	if (!fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	printf("Run summary [PID %d]: %d threads doing pi lock/unlock pairing for %d secs.\n\n",
	       getpid(), nthreads, nsecs);

	init_stats(&throughput_stats);
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_parent, NULL);
	pthread_cond_init(&thread_worker, NULL);

	threads_starting = nthreads;
	pthread_attr_init(&thread_attr);
	gettimeofday(&start, NULL);

	create_threads(worker, thread_attr, cpu);
	pthread_attr_destroy(&thread_attr);

	pthread_mutex_lock(&thread_lock);
	while (threads_starting)
		pthread_cond_wait(&thread_parent, &thread_lock);
	pthread_cond_broadcast(&thread_worker);
	pthread_mutex_unlock(&thread_lock);

	sleep(nsecs);
	toggle_done(0, NULL, NULL);

	for (i = 0; i < nthreads; i++) {
		ret = pthread_join(worker[i].thread, NULL);
		if (ret)
			err(EXIT_FAILURE, "pthread_join");
	}

	/* cleanup & report results */
	pthread_cond_destroy(&thread_parent);
	pthread_cond_destroy(&thread_worker);
	pthread_mutex_destroy(&thread_lock);

	for (i = 0; i < nthreads; i++) {
		unsigned long t = worker[i].ops/runtime.tv_sec;

		update_stats(&throughput_stats, t);
		if (!silent)
			printf("[thread %3d] futex: %p [ %ld ops/sec ]\n",
			       worker[i].tid, worker[i].futex, t);

		if (multi)
			zfree(&worker[i].futex);
	}

	print_summary();

	free(worker);
	return ret;
err:
	usage_with_options(bench_futex_lock_pi_usage, options);
	exit(EXIT_FAILURE);
}