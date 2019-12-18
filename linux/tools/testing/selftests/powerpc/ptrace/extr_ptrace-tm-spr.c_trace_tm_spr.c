#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tm_spr_regs {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_3__ {int /*<<< orphan*/  tm_tfiar; int /*<<< orphan*/  tm_texasr; int /*<<< orphan*/  tm_tfhar; } ;
struct TYPE_4__ {int flag; TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_IF (int /*<<< orphan*/ ) ; 
 int TEST_PASS ; 
 TYPE_2__* pptr ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_tm_spr (int /*<<< orphan*/ ,struct tm_spr_regs*) ; 
 int /*<<< orphan*/  start_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_trace (int /*<<< orphan*/ ) ; 

int trace_tm_spr(pid_t child)
{
	FAIL_IF(start_trace(child));
	FAIL_IF(show_tm_spr(child, (struct tm_spr_regs *)&pptr->regs));

	printf("TFHAR: %lx TEXASR: %lx TFIAR: %lx\n", pptr->regs.tm_tfhar,
				pptr->regs.tm_texasr, pptr->regs.tm_tfiar);

	pptr->flag = 1;
	FAIL_IF(stop_trace(child));

	return TEST_PASS;
}