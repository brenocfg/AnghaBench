#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_sigaction; int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct mq_attr {int mq_maxmsg; int /*<<< orphan*/  mq_msgsize; int /*<<< orphan*/  mq_flags; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  poptContext ;
struct TYPE_4__ {scalar_t__ rlim_cur; scalar_t__ rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CPU_ALLOC (int) ; 
 int /*<<< orphan*/  CPU_ALLOC_SIZE (int) ; 
 int /*<<< orphan*/  CPU_ISSET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_S (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO_S (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_CPUS ; 
 int /*<<< orphan*/  MAX_MSGS ; 
 int /*<<< orphan*/  MAX_MSGSIZE ; 
 int /*<<< orphan*/  MSG_SIZE ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  RLIMIT_MSGQUEUE ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cont_thread ; 
 int continuous_mode ; 
 scalar_t__ continuous_mode_fake ; 
 char* cpu_option_string ; 
 int /*<<< orphan*/ * cpu_set ; 
 int /*<<< orphan*/  cpu_set_size ; 
 int /*<<< orphan*/ * cpu_threads ; 
 int cpus_online ; 
 int* cpus_to_pin ; 
 TYPE_1__ cur_limits ; 
 int cur_max_msgs ; 
 int cur_max_msgsize ; 
 int cur_nice ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fake_cont_thread ; 
 int /*<<< orphan*/  fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get (int /*<<< orphan*/ ) ; 
 int getpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  increase_limits () ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int /*<<< orphan*/  main_thread ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_msgs ; 
 int /*<<< orphan*/  max_msgsize ; 
 int min (int,int) ; 
 int num_cpus_to_pin ; 
 int /*<<< orphan*/  open_queue (struct mq_attr*) ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  perf_test_thread ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poptGetContext (int /*<<< orphan*/ *,int,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int poptGetNextOpt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poptPrintUsage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 char* queue_path ; 
 TYPE_1__ saved_limits ; 
 int saved_max_msgs ; 
 int saved_max_msgsize ; 
 int /*<<< orphan*/  shutdown (long,char*,int) ; 
 int /*<<< orphan*/  sig_action ; 
 int /*<<< orphan*/  sig_action_SIGUSR1 ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[])
{
	struct mq_attr attr;
	char *option, *next_option;
	int i, cpu, rc;
	struct sigaction sa;
	poptContext popt_context;
	void *retval;

	main_thread = pthread_self();
	num_cpus_to_pin = 0;

	if (sysconf(_SC_NPROCESSORS_ONLN) == -1) {
		perror("sysconf(_SC_NPROCESSORS_ONLN)");
		exit(1);
	}
	cpus_online = min(MAX_CPUS, sysconf(_SC_NPROCESSORS_ONLN));
	cpu_set = CPU_ALLOC(cpus_online);
	if (cpu_set == NULL) {
		perror("CPU_ALLOC()");
		exit(1);
	}
	cpu_set_size = CPU_ALLOC_SIZE(cpus_online);
	CPU_ZERO_S(cpu_set_size, cpu_set);

	popt_context = poptGetContext(NULL, argc, (const char **)argv,
				      options, 0);

	while ((rc = poptGetNextOpt(popt_context)) > 0) {
		switch (rc) {
		case 'c':
			continuous_mode = 1;
			option = cpu_option_string;
			do {
				next_option = strchr(option, ',');
				if (next_option)
					*next_option = '\0';
				cpu = atoi(option);
				if (cpu >= cpus_online)
					fprintf(stderr, "CPU %d exceeds "
						"cpus online, ignoring.\n",
						cpu);
				else
					cpus_to_pin[num_cpus_to_pin++] = cpu;
				if (next_option)
					option = ++next_option;
			} while (next_option && num_cpus_to_pin < MAX_CPUS);
			/* Double check that they didn't give us the same CPU
			 * more than once */
			for (cpu = 0; cpu < num_cpus_to_pin; cpu++) {
				if (CPU_ISSET_S(cpus_to_pin[cpu], cpu_set_size,
						cpu_set)) {
					fprintf(stderr, "Any given CPU may "
						"only be given once.\n");
					exit(1);
				} else
					CPU_SET_S(cpus_to_pin[cpu],
						  cpu_set_size, cpu_set);
			}
			break;
		case 'p':
			/*
			 * Although we can create a msg queue with a
			 * non-absolute path name, unlink will fail.  So,
			 * if the name doesn't start with a /, add one
			 * when we save it.
			 */
			option = queue_path;
			if (*option != '/') {
				queue_path = malloc(strlen(option) + 2);
				if (!queue_path) {
					perror("malloc()");
					exit(1);
				}
				queue_path[0] = '/';
				queue_path[1] = 0;
				strcat(queue_path, option);
				free(option);
			}
			break;
		}
	}

	if (continuous_mode && num_cpus_to_pin == 0) {
		fprintf(stderr, "Must pass at least one CPU to continuous "
			"mode.\n");
		poptPrintUsage(popt_context, stderr, 0);
		exit(1);
	} else if (!continuous_mode) {
		num_cpus_to_pin = 1;
		cpus_to_pin[0] = cpus_online - 1;
	}

	if (getuid() != 0)
		ksft_exit_skip("Not running as root, but almost all tests "
			"require root in order to modify\nsystem settings.  "
			"Exiting.\n");

	max_msgs = fopen(MAX_MSGS, "r+");
	max_msgsize = fopen(MAX_MSGSIZE, "r+");
	if (!max_msgs)
		shutdown(2, "Failed to open msg_max", __LINE__);
	if (!max_msgsize)
		shutdown(2, "Failed to open msgsize_max", __LINE__);

	/* Load up the current system values for everything we can */
	getr(RLIMIT_MSGQUEUE, &saved_limits);
	cur_limits = saved_limits;
	saved_max_msgs = cur_max_msgs = get(max_msgs);
	saved_max_msgsize = cur_max_msgsize = get(max_msgsize);
	errno = 0;
	cur_nice = getpriority(PRIO_PROCESS, 0);
	if (errno)
		shutdown(2, "getpriority()", __LINE__);

	/* Tell the user our initial state */
	printf("\nInitial system state:\n");
	printf("\tUsing queue path:\t\t\t%s\n", queue_path);
	printf("\tRLIMIT_MSGQUEUE(soft):\t\t\t%ld\n",
		(long) saved_limits.rlim_cur);
	printf("\tRLIMIT_MSGQUEUE(hard):\t\t\t%ld\n",
		(long) saved_limits.rlim_max);
	printf("\tMaximum Message Size:\t\t\t%d\n", saved_max_msgsize);
	printf("\tMaximum Queue Size:\t\t\t%d\n", saved_max_msgs);
	printf("\tNice value:\t\t\t\t%d\n", cur_nice);
	printf("\n");

	increase_limits();

	printf("Adjusted system state for testing:\n");
	if (cur_limits.rlim_cur == RLIM_INFINITY) {
		printf("\tRLIMIT_MSGQUEUE(soft):\t\t\t(unlimited)\n");
		printf("\tRLIMIT_MSGQUEUE(hard):\t\t\t(unlimited)\n");
	} else {
		printf("\tRLIMIT_MSGQUEUE(soft):\t\t\t%ld\n",
		       (long) cur_limits.rlim_cur);
		printf("\tRLIMIT_MSGQUEUE(hard):\t\t\t%ld\n",
		       (long) cur_limits.rlim_max);
	}
	printf("\tMaximum Message Size:\t\t\t%d\n", cur_max_msgsize);
	printf("\tMaximum Queue Size:\t\t\t%d\n", cur_max_msgs);
	printf("\tNice value:\t\t\t\t%d\n", cur_nice);
	printf("\tContinuous mode:\t\t\t(%s)\n", continuous_mode ?
	       (continuous_mode_fake ? "fake mode" : "enabled") :
	       "disabled");
	printf("\tCPUs to pin:\t\t\t\t%d", cpus_to_pin[0]);
	for (cpu = 1; cpu < num_cpus_to_pin; cpu++)
			printf(",%d", cpus_to_pin[cpu]);
	printf("\n");

	sa.sa_sigaction = sig_action_SIGUSR1;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGHUP);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		shutdown(1, "sigaction(SIGUSR1)", __LINE__);
	sa.sa_sigaction = sig_action;
	if (sigaction(SIGHUP, &sa, NULL) == -1)
		shutdown(1, "sigaction(SIGHUP)", __LINE__);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		shutdown(1, "sigaction(SIGINT)", __LINE__);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		shutdown(1, "sigaction(SIGQUIT)", __LINE__);
	if (sigaction(SIGTERM, &sa, NULL) == -1)
		shutdown(1, "sigaction(SIGTERM)", __LINE__);

	if (!continuous_mode_fake) {
		attr.mq_flags = O_NONBLOCK;
		attr.mq_maxmsg = cur_max_msgs;
		attr.mq_msgsize = MSG_SIZE;
		open_queue(&attr);
	}
	for (i = 0; i < num_cpus_to_pin; i++) {
		pthread_attr_t thread_attr;
		void *thread_func;

		if (continuous_mode_fake)
			thread_func = &fake_cont_thread;
		else if (continuous_mode)
			thread_func = &cont_thread;
		else
			thread_func = &perf_test_thread;

		CPU_ZERO_S(cpu_set_size, cpu_set);
		CPU_SET_S(cpus_to_pin[i], cpu_set_size, cpu_set);
		pthread_attr_init(&thread_attr);
		pthread_attr_setaffinity_np(&thread_attr, cpu_set_size,
					    cpu_set);
		if (pthread_create(&cpu_threads[i], &thread_attr, thread_func,
				   NULL))
			shutdown(1, "pthread_create()", __LINE__);
		pthread_attr_destroy(&thread_attr);
	}

	if (!continuous_mode) {
		pthread_join(cpu_threads[0], &retval);
		shutdown((long)retval, "perf_test_thread()", __LINE__);
	} else {
		while (1)
			sleep(1);
	}
	shutdown(0, "", 0);
}