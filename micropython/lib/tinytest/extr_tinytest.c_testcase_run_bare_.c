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
struct testcase_t {TYPE_1__* setup; int /*<<< orphan*/  (* fn ) (void*) ;} ;
typedef  enum outcome { ____Placeholder_outcome } outcome ;
struct TYPE_2__ {scalar_t__ (* cleanup_fn ) (struct testcase_t const*,void*) ;void* (* setup_fn ) (struct testcase_t const*) ;} ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int SKIP ; 
 scalar_t__ TT_SKIP ; 
 int cur_test_outcome ; 
 void* stub1 (struct testcase_t const*) ; 
 int /*<<< orphan*/  stub2 (void*) ; 
 scalar_t__ stub3 (struct testcase_t const*,void*) ; 

__attribute__((used)) static enum outcome
testcase_run_bare_(const struct testcase_t *testcase)
{
	void *env = NULL;
	int outcome;
	if (testcase->setup) {
		env = testcase->setup->setup_fn(testcase);
		if (!env)
			return FAIL;
		else if (env == (void*)TT_SKIP)
			return SKIP;
	}

	cur_test_outcome = OK;
	testcase->fn(env);
	outcome = cur_test_outcome;

	if (testcase->setup) {
		if (testcase->setup->cleanup_fn(testcase, env) == 0)
			outcome = FAIL;
	}

	return outcome;
}