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

/* Variables and functions */
 int /*<<< orphan*/ * cctx ; 
 int /*<<< orphan*/ * gctx ; 
 int /*<<< orphan*/ * jit_stack ; 
 int /*<<< orphan*/ * mctx ; 
 int /*<<< orphan*/ * mdata ; 
 int /*<<< orphan*/  pcre2_compile_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcre2_general_context_free (int /*<<< orphan*/ *) ; 
 scalar_t__ pcre2_init_ok ; 
 int /*<<< orphan*/  pcre2_jit_stack_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcre2_match_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcre2_match_data_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_pcre_shutdown_pcre2(void)
{/*{{{*/
	if (gctx) {
		pcre2_general_context_free(gctx);
		gctx = NULL;
	}

	if (cctx) {
		pcre2_compile_context_free(cctx);
		cctx = NULL;
	}

	if (mctx) {
		pcre2_match_context_free(mctx);
		mctx = NULL;
	}

#ifdef HAVE_PCRE_JIT_SUPPORT
	/* Stack may only be destroyed when no cached patterns
	 	possibly associated with it do exist. */
	if (jit_stack) {
		pcre2_jit_stack_free(jit_stack);
		jit_stack = NULL;
	}
#endif

	if (mdata) {
		pcre2_match_data_free(mdata);
		mdata = NULL;
	}

	pcre2_init_ok = 0;
}