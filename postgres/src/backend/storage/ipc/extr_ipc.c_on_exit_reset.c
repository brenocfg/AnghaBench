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
 scalar_t__ before_shmem_exit_index ; 
 scalar_t__ on_proc_exit_index ; 
 scalar_t__ on_shmem_exit_index ; 
 int /*<<< orphan*/  reset_on_dsm_detach () ; 

void
on_exit_reset(void)
{
	before_shmem_exit_index = 0;
	on_shmem_exit_index = 0;
	on_proc_exit_index = 0;
	reset_on_dsm_detach();
}