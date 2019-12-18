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
typedef  int /*<<< orphan*/  pg_on_exit_callback ;
struct TYPE_2__ {int /*<<< orphan*/  arg; int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  FATAL ; 
 size_t MAX_ON_EXITS ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit_callback ; 
 int atexit_callback_setup ; 
 size_t before_shmem_exit_index ; 
 TYPE_1__* before_shmem_exit_list ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg_internal (char*) ; 

void
before_shmem_exit(pg_on_exit_callback function, Datum arg)
{
	if (before_shmem_exit_index >= MAX_ON_EXITS)
		ereport(FATAL,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg_internal("out of before_shmem_exit slots")));

	before_shmem_exit_list[before_shmem_exit_index].function = function;
	before_shmem_exit_list[before_shmem_exit_index].arg = arg;

	++before_shmem_exit_index;

	if (!atexit_callback_setup)
	{
		atexit(atexit_callback);
		atexit_callback_setup = true;
	}
}