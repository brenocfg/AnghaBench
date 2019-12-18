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

/* Variables and functions */
 int ENOMEM ; 
 unsigned int WQ_CPU_INTENSIVE ; 
 unsigned int WQ_HIGHPRI ; 
 unsigned int WQ_UNBOUND ; 
 scalar_t__ alloc_workqueue (char*,unsigned int const,unsigned int const) ; 
 unsigned int num_possible_cpus () ; 
 scalar_t__ z_erofs_workqueue ; 

__attribute__((used)) static inline int z_erofs_init_workqueue(void)
{
	const unsigned int onlinecpus = num_possible_cpus();
	const unsigned int flags = WQ_UNBOUND | WQ_HIGHPRI | WQ_CPU_INTENSIVE;

	/*
	 * no need to spawn too many threads, limiting threads could minimum
	 * scheduling overhead, perhaps per-CPU threads should be better?
	 */
	z_erofs_workqueue = alloc_workqueue("erofs_unzipd", flags,
					    onlinecpus + onlinecpus / 4);
	return z_erofs_workqueue ? 0 : -ENOMEM;
}