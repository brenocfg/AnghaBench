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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_PCRE_DEFAULT_EXTRA_COPTIONS ; 
 int /*<<< orphan*/  PHP_PCRE_PREALLOC_MDATA_SIZE ; 
 scalar_t__ cctx ; 
 scalar_t__ gctx ; 
 scalar_t__ mctx ; 
 scalar_t__ mdata ; 
 scalar_t__ pcre2_compile_context_create (scalar_t__) ; 
 scalar_t__ pcre2_general_context_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pcre2_init_ok ; 
 scalar_t__ pcre2_match_context_create (scalar_t__) ; 
 scalar_t__ pcre2_match_data_create (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pcre2_set_compile_extra_options (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_pcre_free ; 
 int /*<<< orphan*/  php_pcre_malloc ; 

__attribute__((used)) static void php_pcre_init_pcre2(uint8_t jit)
{/*{{{*/
	if (!gctx) {
		gctx = pcre2_general_context_create(php_pcre_malloc, php_pcre_free, NULL);
		if (!gctx) {
			pcre2_init_ok = 0;
			return;
		}
	}

	if (!cctx) {
		cctx = pcre2_compile_context_create(gctx);
		if (!cctx) {
			pcre2_init_ok = 0;
			return;
		}
	}

	/* XXX The 'X' modifier is the default behavior in PCRE2. This option is
		called dangerous in the manual, as typos in patterns can cause
		unexpected results. We might want to to switch to the default PCRE2
		behavior, too, thus causing a certain BC break. */
	pcre2_set_compile_extra_options(cctx, PHP_PCRE_DEFAULT_EXTRA_COPTIONS);

	if (!mctx) {
		mctx = pcre2_match_context_create(gctx);
		if (!mctx) {
			pcre2_init_ok = 0;
			return;
		}
	}

#ifdef HAVE_PCRE_JIT_SUPPORT
	if (jit && !jit_stack) {
		jit_stack = pcre2_jit_stack_create(PCRE_JIT_STACK_MIN_SIZE, PCRE_JIT_STACK_MAX_SIZE, gctx);
		if (!jit_stack) {
			pcre2_init_ok = 0;
			return;
		}
	}
#endif

	if (!mdata) {
		mdata = pcre2_match_data_create(PHP_PCRE_PREALLOC_MDATA_SIZE, gctx);
		if (!mdata) {
			pcre2_init_ok = 0;
			return;
		}
	}

	pcre2_init_ok = 1;
}