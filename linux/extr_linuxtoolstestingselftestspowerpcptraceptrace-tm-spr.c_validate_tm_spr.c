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
struct tm_spr_regs {scalar_t__ tm_tfhar; scalar_t__ tm_texasr; scalar_t__ tm_tfiar; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int) ; 
 int TEST_PASS ; 
 scalar_t__ TM_KVM_SCHED ; 
 scalar_t__ tfhar ; 

int validate_tm_spr(struct tm_spr_regs *regs)
{
	FAIL_IF(regs->tm_tfhar != tfhar);
	FAIL_IF((regs->tm_texasr == TM_KVM_SCHED) && (regs->tm_tfiar != 0));

	return TEST_PASS;
}