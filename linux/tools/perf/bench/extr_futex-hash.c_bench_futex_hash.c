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
struct worker {int nr; unsigned int tid; unsigned long ops; int /*<<< orphan*/ * futex; int /*<<< orphan*/  thread; int /*<<< orphan*/ * map; } ;
struct sigaction {int /*<<< orphan*/  (* sa_sigaction ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  sa_mask; } ;
struct perf_cpu_map {int nr; unsigned int tid; unsigned long ops; int /*<<< orphan*/ * futex; int /*<<< orphan*/  thread; int /*<<< orphan*/ * map; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_2__ {unsigned long tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  FUTEX_PRIVATE_FLAG ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  bench_futex_hash_usage ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct worker*) ; 
 scalar_t__ fshared ; 
 int /*<<< orphan*/  futex_flag ; 
 int getpid () ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_stats (int /*<<< orphan*/ *) ; 
 int nfutexes ; 
 int nsecs ; 
 int nthreads ; 
 int /*<<< orphan*/  options ; 
 int parse_options (int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct worker* perf_cpu_map__new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_summary () ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ runtime ; 
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
 int /*<<< orphan*/  workerfn ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ **) ; 

int bench_futex_hash(int argc, const char **argv)
{
	int ret = 0;
	cpu_set_t cpuset;
	struct sigaction act;
	unsigned int i;
	pthread_attr_t thread_attr;
	struct worker *worker = NULL;
	struct perf_cpu_map *cpu;

	argc = parse_options(argc, argv, options, bench_futex_hash_usage, 0);
	if (argc) {
		usage_with_options(bench_futex_hash_usage, options);
		exit(EXIT_FAILURE);
	}

	cpu = perf_cpu_map__new(NULL);
	if (!cpu)
		goto errmem;

	sigfillset(&act.sa_mask);
	act.sa_sigaction = toggle_done;
	sigaction(SIGINT, &act, NULL);

	if (!nthreads) /* default to the number of CPUs */
		nthreads = cpu->nr;

	worker = calloc(nthreads, sizeof(*worker));
	if (!worker)
		goto errmem;

	if (!fshared)
		futex_flag = FUTEX_PRIVATE_FLAG;

	printf("Run summary [PID %d]: %d threads, each operating on %d [%s] futexes for %d secs.\n\n",
	       getpid(), nthreads, nfutexes, fshared ? "shared":"private", nsecs);

	init_stats(&throughput_stats);
	pthread_mutex_init(&thread_lock, NULL);
	pthread_cond_init(&thread_parent, NULL);
	pthread_cond_init(&thread_worker, NULL);

	threads_starting = nthreads;
	pthread_attr_init(&thread_attr);
	gettimeofday(&start, NULL);
	for (i = 0; i < nthreads; i++) {
		worker[i].tid = i;
		worker[i].futex = calloc(nfutexes, sizeof(*worker[i].futex));
		if (!worker[i].futex)
			goto errmem;

		CPU_ZERO(&cpuset);
		CPU_SET(cpu->map[i % cpu->nr], &cpuset);

		ret = pthread_attr_setaffinity_np(&thread_attr, sizeof(cpu_set_t), &cpuset);
		if (ret)
			err(EXIT_FAILURE, "pthread_attr_setaffinity_np");

		ret = pthread_create(&worker[i].thread, &thread_attr, workerfn,
				     (void *)(struct worker *) &worker[i]);
		if (ret)
			err(EXIT_FAILURE, "pthread_create");

	}
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
		if (!silent) {
			if (nfutexes == 1)
				printf("[thread %2d] futex: %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0], t);
			else
				printf("[thread %2d] futexes: %p ... %p [ %ld ops/sec ]\n",
				       worker[i].tid, &worker[i].futex[0],
				       &worker[i].futex[nfutexes-1], t);
		}

		zfree(&worker[i].futex);
	}

	print_summary();

	free(worker);
	free(cpu);
	return ret;
errmem:
	err(EXIT_FAILURE, "calloc");
}