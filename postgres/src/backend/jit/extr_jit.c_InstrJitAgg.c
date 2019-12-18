#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  emission_counter; int /*<<< orphan*/  optimization_counter; int /*<<< orphan*/  inlining_counter; int /*<<< orphan*/  generation_counter; scalar_t__ created_functions; } ;
typedef  TYPE_1__ JitInstrumentation ;

/* Variables and functions */
 int /*<<< orphan*/  INSTR_TIME_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
InstrJitAgg(JitInstrumentation *dst, JitInstrumentation *add)
{
	dst->created_functions += add->created_functions;
	INSTR_TIME_ADD(dst->generation_counter, add->generation_counter);
	INSTR_TIME_ADD(dst->inlining_counter, add->inlining_counter);
	INSTR_TIME_ADD(dst->optimization_counter, add->optimization_counter);
	INSTR_TIME_ADD(dst->emission_counter, add->emission_counter);
}