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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (long,int /*<<< orphan*/ *) ; 
 long CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

void set_affinity(const char *arg)
{
	cpu_set_t cpuset;
	int ret;
	pthread_t self;
	long int cpu;
	char *endptr;

	if (!arg)
		return;

	cpu = strtol(arg, &endptr, 0);
	assert(!*endptr);

	assert(cpu >= 0 && cpu < CPU_SETSIZE);

	self = pthread_self();
	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);

	ret = pthread_setaffinity_np(self, sizeof(cpu_set_t), &cpuset);
	assert(!ret);
}