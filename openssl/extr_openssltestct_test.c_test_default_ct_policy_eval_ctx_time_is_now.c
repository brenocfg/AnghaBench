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
typedef  int time_t ;
typedef  int /*<<< orphan*/  CT_POLICY_EVAL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CT_POLICY_EVAL_CTX_free (int /*<<< orphan*/ *) ; 
 int CT_POLICY_EVAL_CTX_get_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CT_POLICY_EVAL_CTX_new () ; 
 int /*<<< orphan*/  TEST_time_t_le (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  abs (int) ; 
 scalar_t__ difftime (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_default_ct_policy_eval_ctx_time_is_now(void)
{
    int success = 0;
    CT_POLICY_EVAL_CTX *ct_policy_ctx = CT_POLICY_EVAL_CTX_new();
    const time_t default_time =
        (time_t)(CT_POLICY_EVAL_CTX_get_time(ct_policy_ctx) / 1000);
    const time_t time_tolerance = 600;  /* 10 minutes */

    if (!TEST_time_t_le(abs((int)difftime(time(NULL), default_time)),
                        time_tolerance))
        goto end;

    success = 1;
end:
    CT_POLICY_EVAL_CTX_free(ct_policy_ctx);
    return success;
}