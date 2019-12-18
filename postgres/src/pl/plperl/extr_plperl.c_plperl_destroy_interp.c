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
typedef  int /*<<< orphan*/  PerlInterpreter ;

/* Variables and functions */
 int /*<<< orphan*/  FREETMPS ; 
 int /*<<< orphan*/  JMPENV_POP ; 
 int /*<<< orphan*/  JMPENV_PUSH (int) ; 
 int /*<<< orphan*/  LEAVE ; 
 int PERL_EXIT_DESTRUCT_END ; 
 int /*<<< orphan*/  PERL_UNUSED_VAR (int) ; 
 scalar_t__ PL_endav ; 
 int PL_exit_flags ; 
 int /*<<< orphan*/  PL_minus_c ; 
 int /*<<< orphan*/  PL_scopestack_ix ; 
 int /*<<< orphan*/  call_list (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dJMPENV ; 
 int /*<<< orphan*/  dTHX ; 

__attribute__((used)) static void
plperl_destroy_interp(PerlInterpreter **interp)
{
	if (interp && *interp)
	{
		/*
		 * Only a very minimal destruction is performed: - just call END
		 * blocks.
		 *
		 * We could call perl_destruct() but we'd need to audit its actions
		 * very carefully and work-around any that impact us. (Calling
		 * sv_clean_objs() isn't an option because it's not part of perl's
		 * public API so isn't portably available.) Meanwhile END blocks can
		 * be used to perform manual cleanup.
		 */
		dTHX;

		/* Run END blocks - based on perl's perl_destruct() */
		if (PL_exit_flags & PERL_EXIT_DESTRUCT_END)
		{
			dJMPENV;
			int			x = 0;

			JMPENV_PUSH(x);
			PERL_UNUSED_VAR(x);
			if (PL_endav && !PL_minus_c)
				call_list(PL_scopestack_ix, PL_endav);
			JMPENV_POP;
		}
		LEAVE;
		FREETMPS;

		*interp = NULL;
	}
}