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
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_2__ {scalar_t__ (* release_pages ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int BOUNCE_POLL ; 
 int /*<<< orphan*/  area_src ; 
 int /*<<< orphan*/  attr ; 
 int /*<<< orphan*/  background_thread ; 
 int bounces ; 
 int finished ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  locking_thread ; 
 int nr_cpus ; 
 int /*<<< orphan*/ * pipefd ; 
 scalar_t__ pthread_cancel (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uffd_poll_thread ; 
 int /*<<< orphan*/  uffd_read_mutex ; 
 int /*<<< orphan*/  uffd_read_thread ; 
 TYPE_1__* uffd_test_ops ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int stress(unsigned long *userfaults)
{
	unsigned long cpu;
	pthread_t locking_threads[nr_cpus];
	pthread_t uffd_threads[nr_cpus];
	pthread_t background_threads[nr_cpus];
	void **_userfaults = (void **) userfaults;

	finished = 0;
	for (cpu = 0; cpu < nr_cpus; cpu++) {
		if (pthread_create(&locking_threads[cpu], &attr,
				   locking_thread, (void *)cpu))
			return 1;
		if (bounces & BOUNCE_POLL) {
			if (pthread_create(&uffd_threads[cpu], &attr,
					   uffd_poll_thread, (void *)cpu))
				return 1;
		} else {
			if (pthread_create(&uffd_threads[cpu], &attr,
					   uffd_read_thread,
					   &_userfaults[cpu]))
				return 1;
			pthread_mutex_lock(&uffd_read_mutex);
		}
		if (pthread_create(&background_threads[cpu], &attr,
				   background_thread, (void *)cpu))
			return 1;
	}
	for (cpu = 0; cpu < nr_cpus; cpu++)
		if (pthread_join(background_threads[cpu], NULL))
			return 1;

	/*
	 * Be strict and immediately zap area_src, the whole area has
	 * been transferred already by the background treads. The
	 * area_src could then be faulted in in a racy way by still
	 * running uffdio_threads reading zeropages after we zapped
	 * area_src (but they're guaranteed to get -EEXIST from
	 * UFFDIO_COPY without writing zero pages into area_dst
	 * because the background threads already completed).
	 */
	if (uffd_test_ops->release_pages(area_src))
		return 1;


	finished = 1;
	for (cpu = 0; cpu < nr_cpus; cpu++)
		if (pthread_join(locking_threads[cpu], NULL))
			return 1;

	for (cpu = 0; cpu < nr_cpus; cpu++) {
		char c;
		if (bounces & BOUNCE_POLL) {
			if (write(pipefd[cpu*2+1], &c, 1) != 1) {
				fprintf(stderr, "pipefd write error\n");
				return 1;
			}
			if (pthread_join(uffd_threads[cpu], &_userfaults[cpu]))
				return 1;
		} else {
			if (pthread_cancel(uffd_threads[cpu]))
				return 1;
			if (pthread_join(uffd_threads[cpu], NULL))
				return 1;
		}
	}

	return 0;
}