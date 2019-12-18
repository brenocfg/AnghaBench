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
typedef  int /*<<< orphan*/  rtx_insn ;
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_2__ {scalar_t__ calls_alloca; } ;

/* Variables and functions */
 scalar_t__ CALL ; 
 int /*<<< orphan*/  CALL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ MEM ; 
 int /*<<< orphan*/ * NEXT_INSN (int /*<<< orphan*/ *) ; 
 scalar_t__ NOTE ; 
 scalar_t__ NOTE_INSN_CALL_ARG_LOCATION ; 
 scalar_t__ NOTE_KIND (int /*<<< orphan*/ *) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/ * PATTERN (int /*<<< orphan*/ *) ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_DECL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XVECEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  delete_insn_and_edges (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_insns () ; 
 scalar_t__ large_stack_frame () ; 
 scalar_t__ track_function_decl ; 

__attribute__((used)) static unsigned int stackleak_cleanup_execute(void)
{
	rtx_insn *insn, *next;

	if (cfun->calls_alloca)
		return 0;

	if (large_stack_frame())
		return 0;

	/*
	 * Find stackleak_track_stack() calls. Loop through the chain of insns,
	 * which is an RTL representation of the code for a function.
	 *
	 * The example of a matching insn:
	 *  (call_insn 8 4 10 2 (call (mem (symbol_ref ("stackleak_track_stack")
	 *  [flags 0x41] <function_decl 0x7f7cd3302a80 stackleak_track_stack>)
	 *  [0 stackleak_track_stack S1 A8]) (0)) 675 {*call} (expr_list
	 *  (symbol_ref ("stackleak_track_stack") [flags 0x41] <function_decl
	 *  0x7f7cd3302a80 stackleak_track_stack>) (expr_list (0) (nil))) (nil))
	 */
	for (insn = get_insns(); insn; insn = next) {
		rtx body;

		next = NEXT_INSN(insn);

		/* Check the expression code of the insn */
		if (!CALL_P(insn))
			continue;

		/*
		 * Check the expression code of the insn body, which is an RTL
		 * Expression (RTX) describing the side effect performed by
		 * that insn.
		 */
		body = PATTERN(insn);

		if (GET_CODE(body) == PARALLEL)
			body = XVECEXP(body, 0, 0);

		if (GET_CODE(body) != CALL)
			continue;

		/*
		 * Check the first operand of the call expression. It should
		 * be a mem RTX describing the needed subroutine with a
		 * symbol_ref RTX.
		 */
		body = XEXP(body, 0);
		if (GET_CODE(body) != MEM)
			continue;

		body = XEXP(body, 0);
		if (GET_CODE(body) != SYMBOL_REF)
			continue;

		if (SYMBOL_REF_DECL(body) != track_function_decl)
			continue;

		/* Delete the stackleak_track_stack() call */
		delete_insn_and_edges(insn);
#if BUILDING_GCC_VERSION >= 4007 && BUILDING_GCC_VERSION < 8000
		if (GET_CODE(next) == NOTE &&
		    NOTE_KIND(next) == NOTE_INSN_CALL_ARG_LOCATION) {
			insn = next;
			next = NEXT_INSN(insn);
			delete_insn_and_edges(insn);
		}
#endif
	}

	return 0;
}