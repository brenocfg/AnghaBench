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
struct instruction {int /*<<< orphan*/  offset; int /*<<< orphan*/  sec; int /*<<< orphan*/  call_dest; } ;
struct insn_state {scalar_t__ df; scalar_t__ uaccess; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_FUNC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_dest_name (struct instruction*) ; 
 int /*<<< orphan*/  func_uaccess_safe (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int validate_call(struct instruction *insn, struct insn_state *state)
{
	if (state->uaccess && !func_uaccess_safe(insn->call_dest)) {
		WARN_FUNC("call to %s() with UACCESS enabled",
				insn->sec, insn->offset, call_dest_name(insn));
		return 1;
	}

	if (state->df) {
		WARN_FUNC("call to %s() with DF set",
				insn->sec, insn->offset, call_dest_name(insn));
		return 1;
	}

	return 0;
}