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
typedef  double u64 ;
typedef  int /*<<< orphan*/  tname ;
struct timeval {double tv_sec; double tv_usec; } ;
struct thread_data {double runtime_ns; double speed_gbs; double system_time_ns; double user_time_ns; } ;
typedef  scalar_t__ pid_t ;
struct TYPE_3__ {int nr_proc; double nr_tasks; int show_details; int nr_threads; scalar_t__ measure_convergence; scalar_t__ serialize_startup; } ;
struct TYPE_4__ {double nr_tasks_started; double bytes_done; TYPE_1__ p; struct thread_data* threads; int /*<<< orphan*/  startup_done_mutex; int /*<<< orphan*/  start_work_mutex; } ;

/* Variables and functions */
 scalar_t__ BENCH_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 double NSEC_PER_SEC ; 
 double NSEC_PER_USEC ; 
 int /*<<< orphan*/  USEC_PER_MSEC ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 scalar_t__ bench_format ; 
 int /*<<< orphan*/  deinit () ; 
 int /*<<< orphan*/  dprintf (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 TYPE_2__* g ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ init () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 double min (double,double) ; 
 int /*<<< orphan*/  print_res (char const*,double,char*,char*,char*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  tprintf (char*,...) ; 
 int /*<<< orphan*/  usleep (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  worker_process (int) ; 
 scalar_t__* zalloc (int) ; 

__attribute__((used)) static int __bench_numa(const char *name)
{
	struct timeval start, stop, diff;
	u64 runtime_ns_min, runtime_ns_sum;
	pid_t *pids, pid, wpid;
	double delta_runtime;
	double runtime_avg;
	double runtime_sec_max;
	double runtime_sec_min;
	int wait_stat;
	double bytes;
	int i, t, p;

	if (init())
		return -1;

	pids = zalloc(g->p.nr_proc * sizeof(*pids));
	pid = -1;

	/* All threads try to acquire it, this way we can wait for them to start up: */
	pthread_mutex_lock(&g->start_work_mutex);

	if (g->p.serialize_startup) {
		tprintf(" #\n");
		tprintf(" # Startup synchronization: ..."); fflush(stdout);
	}

	gettimeofday(&start, NULL);

	for (i = 0; i < g->p.nr_proc; i++) {
		pid = fork();
		dprintf(" # process %2d: PID %d\n", i, pid);

		BUG_ON(pid < 0);
		if (!pid) {
			/* Child process: */
			worker_process(i);

			exit(0);
		}
		pids[i] = pid;

	}
	/* Wait for all the threads to start up: */
	while (g->nr_tasks_started != g->p.nr_tasks)
		usleep(USEC_PER_MSEC);

	BUG_ON(g->nr_tasks_started != g->p.nr_tasks);

	if (g->p.serialize_startup) {
		double startup_sec;

		pthread_mutex_lock(&g->startup_done_mutex);

		/* This will start all threads: */
		pthread_mutex_unlock(&g->start_work_mutex);

		/* This mutex is locked - the last started thread will wake us: */
		pthread_mutex_lock(&g->startup_done_mutex);

		gettimeofday(&stop, NULL);

		timersub(&stop, &start, &diff);

		startup_sec = diff.tv_sec * NSEC_PER_SEC;
		startup_sec += diff.tv_usec * NSEC_PER_USEC;
		startup_sec /= NSEC_PER_SEC;

		tprintf(" threads initialized in %.6f seconds.\n", startup_sec);
		tprintf(" #\n");

		start = stop;
		pthread_mutex_unlock(&g->startup_done_mutex);
	} else {
		gettimeofday(&start, NULL);
	}

	/* Parent process: */


	for (i = 0; i < g->p.nr_proc; i++) {
		wpid = waitpid(pids[i], &wait_stat, 0);
		BUG_ON(wpid < 0);
		BUG_ON(!WIFEXITED(wait_stat));

	}

	runtime_ns_sum = 0;
	runtime_ns_min = -1LL;

	for (t = 0; t < g->p.nr_tasks; t++) {
		u64 thread_runtime_ns = g->threads[t].runtime_ns;

		runtime_ns_sum += thread_runtime_ns;
		runtime_ns_min = min(thread_runtime_ns, runtime_ns_min);
	}

	gettimeofday(&stop, NULL);
	timersub(&stop, &start, &diff);

	BUG_ON(bench_format != BENCH_FORMAT_DEFAULT);

	tprintf("\n ###\n");
	tprintf("\n");

	runtime_sec_max = diff.tv_sec * NSEC_PER_SEC;
	runtime_sec_max += diff.tv_usec * NSEC_PER_USEC;
	runtime_sec_max /= NSEC_PER_SEC;

	runtime_sec_min = runtime_ns_min / NSEC_PER_SEC;

	bytes = g->bytes_done;
	runtime_avg = (double)runtime_ns_sum / g->p.nr_tasks / NSEC_PER_SEC;

	if (g->p.measure_convergence) {
		print_res(name, runtime_sec_max,
			"secs,", "NUMA-convergence-latency", "secs latency to NUMA-converge");
	}

	print_res(name, runtime_sec_max,
		"secs,", "runtime-max/thread",	"secs slowest (max) thread-runtime");

	print_res(name, runtime_sec_min,
		"secs,", "runtime-min/thread",	"secs fastest (min) thread-runtime");

	print_res(name, runtime_avg,
		"secs,", "runtime-avg/thread",	"secs average thread-runtime");

	delta_runtime = (runtime_sec_max - runtime_sec_min)/2.0;
	print_res(name, delta_runtime / runtime_sec_max * 100.0,
		"%,", "spread-runtime/thread",	"% difference between max/avg runtime");

	print_res(name, bytes / g->p.nr_tasks / 1e9,
		"GB,", "data/thread",		"GB data processed, per thread");

	print_res(name, bytes / 1e9,
		"GB,", "data-total",		"GB data processed, total");

	print_res(name, runtime_sec_max * NSEC_PER_SEC / (bytes / g->p.nr_tasks),
		"nsecs,", "runtime/byte/thread","nsecs/byte/thread runtime");

	print_res(name, bytes / g->p.nr_tasks / 1e9 / runtime_sec_max,
		"GB/sec,", "thread-speed",	"GB/sec/thread speed");

	print_res(name, bytes / runtime_sec_max / 1e9,
		"GB/sec,", "total-speed",	"GB/sec total speed");

	if (g->p.show_details >= 2) {
		char tname[14 + 2 * 10 + 1];
		struct thread_data *td;
		for (p = 0; p < g->p.nr_proc; p++) {
			for (t = 0; t < g->p.nr_threads; t++) {
				memset(tname, 0, sizeof(tname));
				td = g->threads + p*g->p.nr_threads + t;
				snprintf(tname, sizeof(tname), "process%d:thread%d", p, t);
				print_res(tname, td->speed_gbs,
					"GB/sec",	"thread-speed", "GB/sec/thread speed");
				print_res(tname, td->system_time_ns / NSEC_PER_SEC,
					"secs",	"thread-system-time", "system CPU time/thread");
				print_res(tname, td->user_time_ns / NSEC_PER_SEC,
					"secs",	"thread-user-time", "user CPU time/thread");
			}
		}
	}

	free(pids);

	deinit();

	return 0;
}