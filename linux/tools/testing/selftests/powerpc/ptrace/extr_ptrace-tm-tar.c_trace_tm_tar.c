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
 int /*<<< orphan*/  DSCR_1 ; 
 int /*<<< orphan*/  DSCR_2 ; 
 unsigned long DSCR_4 ; 
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPR_1 ; 
 int /*<<< orphan*/  PPR_2 ; 
 unsigned long PPR_4 ; 
 int /*<<< orphan*/  TAR_1 ; 
 int /*<<< orphan*/  TAR_2 ; 
 int TAR_4 ; 
 int TEST_PASS ; 
 int* pptr ; 
 int /*<<< orphan*/  printf (char*,char*,int,unsigned long,unsigned long) ; 
 char* ptrace_read_ckpt ; 
 char* ptrace_read_running ; 
 char* ptrace_write_ckpt ; 
 int /*<<< orphan*/  show_tar_registers (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  show_tm_checkpointed_state (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  start_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_tar_registers (unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ckpt_tar_registers (int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 

int trace_tm_tar(pid_t child)
{
	unsigned long regs[3];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_tar_registers(child, regs));
	printf("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			ptrace_read_running, regs[0], regs[1], regs[2]);

	FAIL_IF(validate_tar_registers(regs, TAR_2, PPR_2, DSCR_2));
	FAIL_IF(show_tm_checkpointed_state(child, regs));
	printf("%-30s TAR: %lu PPR: %lx DSCR: %lu\n",
			ptrace_read_ckpt, regs[0], regs[1], regs[2]);

	FAIL_IF(validate_tar_registers(regs, TAR_1, PPR_1, DSCR_1));
	FAIL_IF(write_ckpt_tar_registers(child, TAR_4, PPR_4, DSCR_4));
	printf("%-30s TAR: %u PPR: %lx DSCR: %u\n",
			ptrace_write_ckpt, TAR_4, PPR_4, DSCR_4);

	pptr[0] = 1;
	FAIL_IF(stop_trace(child));
	return TEST_PASS;
}