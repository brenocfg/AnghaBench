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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_2 ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPR_2 ; 
 int TAR_2 ; 
 int TEST_PASS ; 
 int /*<<< orphan*/  printf (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* ptrace_write_running ; 
 int /*<<< orphan*/  start_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_tar_registers (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int trace_tar_write(pid_t child)
{
	FAIL_IF(start_trace(child));
	FAIL_IF(write_tar_registers(child, TAR_2, PPR_2, DSCR_2));
	printf("%-30s TAR: %u PPR: %lx DSCR: %u\n",
			ptrace_write_running, TAR_2, PPR_2, DSCR_2);

	FAIL_IF(stop_trace(child));
	return TEST_PASS;
}