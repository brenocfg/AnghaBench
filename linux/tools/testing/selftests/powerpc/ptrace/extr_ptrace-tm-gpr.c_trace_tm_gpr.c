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
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPR_1_REP ; 
 int /*<<< orphan*/  FPR_2_REP ; 
 int /*<<< orphan*/  FPR_3_REP ; 
 int /*<<< orphan*/  GPR_1 ; 
 int /*<<< orphan*/  GPR_2 ; 
 int /*<<< orphan*/  GPR_3 ; 
 int TEST_PASS ; 
 int* pptr ; 
 int /*<<< orphan*/  show_ckpt_fpr (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  show_ckpt_gpr (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  show_fpr (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  show_gpr (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  start_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_fpr (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_gpr (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ckpt_fpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_ckpt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int trace_tm_gpr(pid_t child)
{
	unsigned long gpr[18];
	unsigned long fpr[32];

	FAIL_IF(start_trace(child));
	FAIL_IF(show_gpr(child, gpr));
	FAIL_IF(validate_gpr(gpr, GPR_2));
	FAIL_IF(show_fpr(child, fpr));
	FAIL_IF(validate_fpr(fpr, FPR_2_REP));
	FAIL_IF(show_ckpt_fpr(child, fpr));
	FAIL_IF(validate_fpr(fpr, FPR_1_REP));
	FAIL_IF(show_ckpt_gpr(child, gpr));
	FAIL_IF(validate_gpr(gpr, GPR_1));
	FAIL_IF(write_ckpt_gpr(child, GPR_3));
	FAIL_IF(write_ckpt_fpr(child, FPR_3_REP));

	pptr[0] = 1;
	FAIL_IF(stop_trace(child));

	return TEST_PASS;
}