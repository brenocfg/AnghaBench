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
typedef  int /*<<< orphan*/  pthread_attr_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int cpu ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  iterations ; 
 int /*<<< orphan*/  null_fn ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setaffinity_np (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bench_thread(void)
{
	pthread_t tid;
	cpu_set_t cpuset;
	pthread_attr_t attr;
	int rc;

	rc = pthread_attr_init(&attr);
	if (rc) {
		errno = rc;
		perror("pthread_attr_init");
		exit(1);
	}

	if (cpu != -1) {
		CPU_ZERO(&cpuset);
		CPU_SET(cpu, &cpuset);

		rc = pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
		if (rc) {
			errno = rc;
			perror("pthread_attr_setaffinity_np");
			exit(1);
		}
	}

	while (1) {
		rc = pthread_create(&tid, &attr, null_fn, NULL);
		if (rc) {
			errno = rc;
			perror("pthread_create");
			exit(1);
		}
		rc = pthread_join(tid, NULL);
		if (rc) {
			errno = rc;
			perror("pthread_join");
			exit(1);
		}
		iterations++;
	}
}