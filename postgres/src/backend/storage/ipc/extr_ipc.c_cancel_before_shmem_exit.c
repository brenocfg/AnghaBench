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
typedef  scalar_t__ pg_on_exit_callback ;
struct TYPE_2__ {scalar_t__ function; scalar_t__ arg; } ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int before_shmem_exit_index ; 
 TYPE_1__* before_shmem_exit_list ; 

void
cancel_before_shmem_exit(pg_on_exit_callback function, Datum arg)
{
	if (before_shmem_exit_index > 0 &&
		before_shmem_exit_list[before_shmem_exit_index - 1].function
		== function &&
		before_shmem_exit_list[before_shmem_exit_index - 1].arg == arg)
		--before_shmem_exit_index;
}