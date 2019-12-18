#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * log_cb; } ;
struct TYPE_6__ {TYPE_2__* ctx; } ;
typedef  TYPE_1__ OSSL_CMP_CTX_TEST_FIXTURE ;
typedef  TYPE_2__ OSSL_CMP_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CMP_R_INVALID_ARGS ; 
 int /*<<< orphan*/  CMP_R_MULTIPLE_SAN_SOURCES ; 
 int /*<<< orphan*/  CMP_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CMPerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_CMP_CTX_print_errors (TYPE_2__*) ; 
 int OSSL_CMP_CTX_set_log_cb (TYPE_2__*,int /*<<< orphan*/ *) ; 
 char* STR_SEP ; 
 int /*<<< orphan*/  TEST_int_eq (scalar_t__,int) ; 
 int /*<<< orphan*/  TEST_true (int) ; 
 char* max_str_literal ; 
 scalar_t__ msg_total_size ; 
 int /*<<< orphan*/ * msg_total_size_log_cb ; 
 int /*<<< orphan*/  ossl_cmp_add_error_data (char*) ; 
 int /*<<< orphan*/  ossl_cmp_add_error_line (char*) ; 
 int /*<<< orphan*/  ossl_cmp_add_error_txt (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int execute_CTX_print_errors_test(OSSL_CMP_CTX_TEST_FIXTURE *fixture)
{
    OSSL_CMP_CTX *ctx = fixture->ctx;
    int base_err_msg_size, expected_size;
    int res = 1;

    if (!TEST_true(OSSL_CMP_CTX_set_log_cb(ctx, NULL)))
        res = 0;
    if (!TEST_true(ctx->log_cb == NULL))
        res = 0;

# ifndef OPENSSL_NO_STDIO
    CMPerr(0, CMP_R_MULTIPLE_SAN_SOURCES);
    OSSL_CMP_CTX_print_errors(ctx); /* should print above error to STDERR */
# endif

    /* this should work regardless of OPENSSL_NO_STDIO and OPENSSL_NO_TRACE: */
    if (!TEST_true(OSSL_CMP_CTX_set_log_cb(ctx, msg_total_size_log_cb)))
        res = 0;
    if (!TEST_true(ctx->log_cb == msg_total_size_log_cb)) {
        res = 0;
    } else {
        CMPerr(0, CMP_R_INVALID_ARGS);
        base_err_msg_size = strlen("INVALID_ARGS");
        CMPerr(0, CMP_R_NULL_ARGUMENT);
        base_err_msg_size += strlen("NULL_ARGUMENT");
        expected_size = base_err_msg_size;
        ossl_cmp_add_error_data("data1"); /* should prepend separator " : " */
        expected_size += strlen(" : " "data1");
        ossl_cmp_add_error_data("data2"); /* should prepend separator " : " */
        expected_size += strlen(" : " "data2");
        ossl_cmp_add_error_line("new line"); /* should prepend separator "\n" */
        expected_size += strlen("\n" "new line");
        OSSL_CMP_CTX_print_errors(ctx);
        if (!TEST_int_eq(msg_total_size, expected_size))
            res = 0;

        CMPerr(0, CMP_R_INVALID_ARGS);
        base_err_msg_size = strlen("INVALID_ARGS") + strlen(" : ");
        expected_size = base_err_msg_size;
        while (expected_size < 4096) { /* force split */
            ossl_cmp_add_error_txt(STR_SEP, max_str_literal);
            expected_size += strlen(STR_SEP) + strlen(max_str_literal);
        }
        expected_size += base_err_msg_size - 2 * strlen(STR_SEP);
        msg_total_size = 0;
        OSSL_CMP_CTX_print_errors(ctx);
        if (!TEST_int_eq(msg_total_size, expected_size))
            res = 0;
    }

    return res;
}