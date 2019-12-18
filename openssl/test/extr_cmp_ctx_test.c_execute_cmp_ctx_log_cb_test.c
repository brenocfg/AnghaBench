#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ OSSL_CMP_CTX_TEST_FIXTURE ;
typedef  int /*<<< orphan*/  OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ALL ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ OPENSSL_LINE ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set_log_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_set_log_verbosity (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_DEBUG ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_ERR ; 
 int /*<<< orphan*/  OSSL_CMP_LOG_INFO ; 
 int /*<<< orphan*/  OSSL_CMP_debug (char*) ; 
 int /*<<< orphan*/  OSSL_CMP_err (char*) ; 
 int /*<<< orphan*/  OSSL_CMP_log2 (int /*<<< orphan*/ ,char*,char*,char) ; 
 int /*<<< orphan*/  OSSL_CMP_log_close () ; 
 int /*<<< orphan*/  OSSL_CMP_log_open () ; 
 int /*<<< orphan*/  OSSL_CMP_warn (char*) ; 
 int /*<<< orphan*/  OSSL_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_log_cb ; 
 int test_log_cb_res ; 
 scalar_t__ test_log_line ; 

__attribute__((used)) static int execute_cmp_ctx_log_cb_test(OSSL_CMP_CTX_TEST_FIXTURE *fixture)
{
    int res = 1;
#if !defined OPENSSL_NO_TRACE && !defined OPENSSL_NO_STDIO
    OSSL_CMP_CTX *ctx = fixture->ctx;

    OSSL_TRACE(ALL, "this general trace message is not shown by default\n");

    OSSL_CMP_log_open();
    OSSL_CMP_log_open(); /* multiple calls should be harmless */

    if (!TEST_true(OSSL_CMP_CTX_set_log_cb(ctx, NULL))) {
        res = 0;
    } else {
        OSSL_CMP_err("this should be printed as CMP error message");
        OSSL_CMP_warn("this should be printed as CMP warning message");
        OSSL_CMP_debug("this should not be printed");
        TEST_true(OSSL_CMP_CTX_set_log_verbosity(ctx, OSSL_CMP_LOG_DEBUG));
        OSSL_CMP_debug("this should be printed as CMP debug message");
        TEST_true(OSSL_CMP_CTX_set_log_verbosity(ctx, OSSL_CMP_LOG_INFO));
    }
    if (!TEST_true(OSSL_CMP_CTX_set_log_cb(ctx, test_log_cb))) {
        res = 0;
    } else {
        test_log_line = OPENSSL_LINE + 1;
        OSSL_CMP_log2(INFO, "%s%c", "o", 'k');
        if (!TEST_int_eq(test_log_cb_res, 1))
            res = 0;
        OSSL_CMP_CTX_set_log_verbosity(ctx, OSSL_CMP_LOG_ERR);
        test_log_cb_res = -1; /* callback should not be called at all */
        test_log_line = OPENSSL_LINE + 1;
        OSSL_CMP_log2(INFO, "%s%c", "o", 'k');
        if (!TEST_int_eq(test_log_cb_res, -1))
            res = 0;
    }
    OSSL_CMP_log_close();
    OSSL_CMP_log_close(); /* multiple calls should be harmless */
#endif
    return res;
}