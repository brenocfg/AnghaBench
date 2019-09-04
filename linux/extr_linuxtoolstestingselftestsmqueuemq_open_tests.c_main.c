#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mq_attr {int mq_maxmsg; int mq_msgsize; } ;
struct TYPE_5__ {int rlim_cur; int rlim_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_MSGS ; 
 int /*<<< orphan*/  DEF_MSGSIZE ; 
 int /*<<< orphan*/  MAX_MSGS ; 
 int /*<<< orphan*/  MAX_MSGSIZE ; 
 int /*<<< orphan*/  RLIMIT_MSGQUEUE ; 
 int cur_def_msgs ; 
 int cur_def_msgsize ; 
 TYPE_1__ cur_limits ; 
 int cur_max_msgs ; 
 int cur_max_msgsize ; 
 scalar_t__ def_msgs ; 
 scalar_t__ def_msgsize ; 
 char* default_queue_path ; 
 int default_settings ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fopen (int /*<<< orphan*/ ,char*) ; 
 int get (scalar_t__) ; 
 int /*<<< orphan*/  getr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ max_msgs ; 
 scalar_t__ max_msgsize ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* queue_path ; 
 int saved_def_msgs ; 
 int saved_def_msgsize ; 
 TYPE_1__ saved_limits ; 
 int saved_max_msgs ; 
 int saved_max_msgsize ; 
 int /*<<< orphan*/  set (scalar_t__,int) ; 
 int seteuid (int) ; 
 int /*<<< orphan*/  setr (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  shutdown (int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  test_queue (int /*<<< orphan*/ *,struct mq_attr*) ; 
 scalar_t__ test_queue_fail (struct mq_attr*,struct mq_attr*) ; 
 int /*<<< orphan*/  validate_current_settings () ; 

int main(int argc, char *argv[])
{
	struct mq_attr attr, result;

	if (argc != 2) {
		printf("Using Default queue path - %s\n", default_queue_path);
		queue_path = default_queue_path;
	} else {

	/*
	 * Although we can create a msg queue with a non-absolute path name,
	 * unlink will fail.  So, if the name doesn't start with a /, add one
	 * when we save it.
	 */
		if (*argv[1] == '/')
			queue_path = strdup(argv[1]);
		else {
			queue_path = malloc(strlen(argv[1]) + 2);
			if (!queue_path) {
				perror("malloc()");
				exit(1);
			}
			queue_path[0] = '/';
			queue_path[1] = 0;
			strcat(queue_path, argv[1]);
		}
	}

	if (getuid() != 0)
		ksft_exit_skip("Not running as root, but almost all tests "
			"require root in order to modify\nsystem settings.  "
			"Exiting.\n");

	/* Find out what files there are for us to make tweaks in */
	def_msgs = fopen(DEF_MSGS, "r+");
	def_msgsize = fopen(DEF_MSGSIZE, "r+");
	max_msgs = fopen(MAX_MSGS, "r+");
	max_msgsize = fopen(MAX_MSGSIZE, "r+");

	if (!max_msgs)
		shutdown(2, "Failed to open msg_max", __LINE__);
	if (!max_msgsize)
		shutdown(2, "Failed to open msgsize_max", __LINE__);
	if (def_msgs || def_msgsize)
		default_settings = 1;

	/* Load up the current system values for everything we can */
	getr(RLIMIT_MSGQUEUE, &saved_limits);
	cur_limits = saved_limits;
	if (default_settings) {
		saved_def_msgs = cur_def_msgs = get(def_msgs);
		saved_def_msgsize = cur_def_msgsize = get(def_msgsize);
	}
	saved_max_msgs = cur_max_msgs = get(max_msgs);
	saved_max_msgsize = cur_max_msgsize = get(max_msgsize);

	/* Tell the user our initial state */
	printf("\nInitial system state:\n");
	printf("\tUsing queue path:\t\t%s\n", queue_path);
	printf("\tRLIMIT_MSGQUEUE(soft):\t\t%ld\n",
		(long) saved_limits.rlim_cur);
	printf("\tRLIMIT_MSGQUEUE(hard):\t\t%ld\n",
		(long) saved_limits.rlim_max);
	printf("\tMaximum Message Size:\t\t%d\n", saved_max_msgsize);
	printf("\tMaximum Queue Size:\t\t%d\n", saved_max_msgs);
	if (default_settings) {
		printf("\tDefault Message Size:\t\t%d\n", saved_def_msgsize);
		printf("\tDefault Queue Size:\t\t%d\n", saved_def_msgs);
	} else {
		printf("\tDefault Message Size:\t\tNot Supported\n");
		printf("\tDefault Queue Size:\t\tNot Supported\n");
	}
	printf("\n");

	validate_current_settings();

	printf("Adjusted system state for testing:\n");
	printf("\tRLIMIT_MSGQUEUE(soft):\t\t%ld\n", (long) cur_limits.rlim_cur);
	printf("\tRLIMIT_MSGQUEUE(hard):\t\t%ld\n", (long) cur_limits.rlim_max);
	printf("\tMaximum Message Size:\t\t%d\n", cur_max_msgsize);
	printf("\tMaximum Queue Size:\t\t%d\n", cur_max_msgs);
	if (default_settings) {
		printf("\tDefault Message Size:\t\t%d\n", cur_def_msgsize);
		printf("\tDefault Queue Size:\t\t%d\n", cur_def_msgs);
	}

	printf("\n\nTest series 1, behavior when no attr struct "
	       "passed to mq_open:\n");
	if (!default_settings) {
		test_queue(NULL, &result);
		printf("Given sane system settings, mq_open without an attr "
		       "struct succeeds:\tPASS\n");
		if (result.mq_maxmsg != cur_max_msgs ||
		    result.mq_msgsize != cur_max_msgsize) {
			printf("Kernel does not support setting the default "
			       "mq attributes,\nbut also doesn't tie the "
			       "defaults to the maximums:\t\t\tPASS\n");
		} else {
			set(max_msgs, ++cur_max_msgs);
			set(max_msgsize, ++cur_max_msgsize);
			test_queue(NULL, &result);
			if (result.mq_maxmsg == cur_max_msgs &&
			    result.mq_msgsize == cur_max_msgsize)
				printf("Kernel does not support setting the "
				       "default mq attributes and\n"
				       "also ties system wide defaults to "
				       "the system wide maximums:\t\t"
				       "FAIL\n");
			else
				printf("Kernel does not support setting the "
				       "default mq attributes,\n"
				       "but also doesn't tie the defaults to "
				       "the maximums:\t\t\tPASS\n");
		}
	} else {
		printf("Kernel supports setting defaults separately from "
		       "maximums:\t\tPASS\n");
		/*
		 * While we are here, go ahead and test that the kernel
		 * properly follows the default settings
		 */
		test_queue(NULL, &result);
		printf("Given sane values, mq_open without an attr struct "
		       "succeeds:\t\tPASS\n");
		if (result.mq_maxmsg != cur_def_msgs ||
		    result.mq_msgsize != cur_def_msgsize)
			printf("Kernel supports setting defaults, but does "
			       "not actually honor them:\tFAIL\n\n");
		else {
			set(def_msgs, ++cur_def_msgs);
			set(def_msgsize, ++cur_def_msgsize);
			/* In case max was the same as the default */
			set(max_msgs, ++cur_max_msgs);
			set(max_msgsize, ++cur_max_msgsize);
			test_queue(NULL, &result);
			if (result.mq_maxmsg != cur_def_msgs ||
			    result.mq_msgsize != cur_def_msgsize)
				printf("Kernel supports setting defaults, but "
				       "does not actually honor them:\t"
				       "FAIL\n");
			else
				printf("Kernel properly honors default setting "
				       "knobs:\t\t\t\tPASS\n");
		}
		set(def_msgs, cur_max_msgs + 1);
		cur_def_msgs = cur_max_msgs + 1;
		set(def_msgsize, cur_max_msgsize + 1);
		cur_def_msgsize = cur_max_msgsize + 1;
		if (cur_def_msgs * (cur_def_msgsize + 2 * sizeof(void *)) >=
		    cur_limits.rlim_cur) {
			cur_limits.rlim_cur = (cur_def_msgs + 2) *
				(cur_def_msgsize + 2 * sizeof(void *));
			cur_limits.rlim_max = 2 * cur_limits.rlim_cur;
			setr(RLIMIT_MSGQUEUE, &cur_limits);
		}
		if (test_queue_fail(NULL, &result)) {
			if (result.mq_maxmsg == cur_max_msgs &&
			    result.mq_msgsize == cur_max_msgsize)
				printf("Kernel properly limits default values "
				       "to lesser of default/max:\t\tPASS\n");
			else
				printf("Kernel does not properly set default "
				       "queue parameters when\ndefaults > "
				       "max:\t\t\t\t\t\t\t\tFAIL\n");
		} else
			printf("Kernel fails to open mq because defaults are "
			       "greater than maximums:\tFAIL\n");
		set(def_msgs, --cur_def_msgs);
		set(def_msgsize, --cur_def_msgsize);
		cur_limits.rlim_cur = cur_limits.rlim_max = cur_def_msgs *
			cur_def_msgsize;
		setr(RLIMIT_MSGQUEUE, &cur_limits);
		if (test_queue_fail(NULL, &result))
			printf("Kernel creates queue even though defaults "
			       "would exceed\nrlimit setting:"
			       "\t\t\t\t\t\t\t\tFAIL\n");
		else
			printf("Kernel properly fails to create queue when "
			       "defaults would\nexceed rlimit:"
			       "\t\t\t\t\t\t\t\tPASS\n");
	}

	/*
	 * Test #2 - open with an attr struct that exceeds rlimit
	 */
	printf("\n\nTest series 2, behavior when attr struct is "
	       "passed to mq_open:\n");
	cur_max_msgs = 32;
	cur_max_msgsize = cur_limits.rlim_max >> 4;
	set(max_msgs, cur_max_msgs);
	set(max_msgsize, cur_max_msgsize);
	attr.mq_maxmsg = cur_max_msgs;
	attr.mq_msgsize = cur_max_msgsize;
	if (test_queue_fail(&attr, &result))
		printf("Queue open in excess of rlimit max when euid = 0 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open in excess of rlimit max when euid = 0 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = cur_max_msgs + 1;
	attr.mq_msgsize = 10;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with mq_maxmsg > limit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	else
		printf("Queue open with mq_maxmsg > limit when euid = 0 "
		       "failed:\t\tFAIL\n");
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = cur_max_msgsize + 1;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with mq_msgsize > limit when euid = 0 "
		       "succeeded:\t\tPASS\n");
	else
		printf("Queue open with mq_msgsize > limit when euid = 0 "
		       "failed:\t\tFAIL\n");
	attr.mq_maxmsg = 65536;
	attr.mq_msgsize = 65536;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with total size > 2GB when euid = 0 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open with total size > 2GB when euid = 0 "
		       "failed:\t\t\tPASS\n");

	if (seteuid(99) == -1) {
		perror("seteuid() failed");
		exit(1);
	}

	attr.mq_maxmsg = cur_max_msgs;
	attr.mq_msgsize = cur_max_msgsize;
	if (test_queue_fail(&attr, &result))
		printf("Queue open in excess of rlimit max when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open in excess of rlimit max when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = cur_max_msgs + 1;
	attr.mq_msgsize = 10;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with mq_maxmsg > limit when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open with mq_maxmsg > limit when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = 1;
	attr.mq_msgsize = cur_max_msgsize + 1;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with mq_msgsize > limit when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open with mq_msgsize > limit when euid = 99 "
		       "failed:\t\tPASS\n");
	attr.mq_maxmsg = 65536;
	attr.mq_msgsize = 65536;
	if (test_queue_fail(&attr, &result))
		printf("Queue open with total size > 2GB when euid = 99 "
		       "succeeded:\t\tFAIL\n");
	else
		printf("Queue open with total size > 2GB when euid = 99 "
		       "failed:\t\t\tPASS\n");

	shutdown(0,"",0);
}