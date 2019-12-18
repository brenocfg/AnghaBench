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
struct perf_event_attr {int dummy; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NPROCESSORS_CONF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_on_cpu (int,struct perf_event_attr*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_perf_event_array(struct perf_event_attr *attr,
				  const char *name)
{
	int i, status, nr_cpus = sysconf(_SC_NPROCESSORS_CONF);
	pid_t pid[nr_cpus];
	int err = 0;

	printf("Test reading %s counters\n", name);

	for (i = 0; i < nr_cpus; i++) {
		pid[i] = fork();
		assert(pid[i] >= 0);
		if (pid[i] == 0) {
			check_on_cpu(i, attr);
			exit(1);
		}
	}

	for (i = 0; i < nr_cpus; i++) {
		assert(waitpid(pid[i], &status, 0) == pid[i]);
		err |= status;
	}

	if (err)
		printf("Test: %s FAILED\n", name);
}