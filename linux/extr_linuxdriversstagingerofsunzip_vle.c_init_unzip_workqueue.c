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
 int WQ_CPU_INTENSIVE ; 
 int WQ_HIGHPRI ; 
 int WQ_UNBOUND ; 
 int /*<<< orphan*/ * alloc_workqueue (char*,int,unsigned int const) ; 
 unsigned int num_possible_cpus () ; 
 int /*<<< orphan*/ * z_erofs_workqueue ; 

__attribute__((used)) static inline int init_unzip_workqueue(void)
{
	const unsigned onlinecpus = num_possible_cpus();

	/*
	 * we don't need too many threads, limiting threads
	 * could improve scheduling performance.
	 */
	z_erofs_workqueue = alloc_workqueue("erofs_unzipd",
		WQ_UNBOUND | WQ_HIGHPRI | WQ_CPU_INTENSIVE,
		onlinecpus + onlinecpus / 4);

	return z_erofs_workqueue != NULL ? 0 : -ENOMEM;
}