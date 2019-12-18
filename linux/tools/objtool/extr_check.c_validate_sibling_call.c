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
struct instruction {int /*<<< orphan*/  offset; int /*<<< orphan*/  sec; } ;
struct insn_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_FUNC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ has_modified_stack_frame (struct insn_state*) ; 
 int validate_call (struct instruction*,struct insn_state*) ; 

__attribute__((used)) static int validate_sibling_call(struct instruction *insn, struct insn_state *state)
{
	if (has_modified_stack_frame(state)) {
		WARN_FUNC("sibling call from callable instruction with modified stack frame",
				insn->sec, insn->offset);
		return 1;
	}

	return validate_call(insn, state);
}