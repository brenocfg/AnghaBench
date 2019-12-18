#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* err; TYPE_1__* data; } ;
struct TYPE_5__ {scalar_t__ (* keyop ) (unsigned char*,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;unsigned char* ctx; int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  input_len; int /*<<< orphan*/  input; } ;
typedef  TYPE_1__ PKEY_DATA ;
typedef  TYPE_2__ EVP_TEST ;
typedef  unsigned char EVP_PKEY_CTX ;

/* Variables and functions */
 unsigned char* EVP_PKEY_CTX_dup (unsigned char*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (unsigned char*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  memory_err_compare (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 scalar_t__ stub1 (unsigned char*,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (unsigned char*,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (unsigned char*,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (unsigned char*,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkey_test_run(EVP_TEST *t)
{
    PKEY_DATA *expected = t->data;
    unsigned char *got = NULL;
    size_t got_len;
    EVP_PKEY_CTX *copy = NULL;

    if (expected->keyop(expected->ctx, NULL, &got_len,
                        expected->input, expected->input_len) <= 0
            || !TEST_ptr(got = OPENSSL_malloc(got_len))) {
        t->err = "KEYOP_LENGTH_ERROR";
        goto err;
    }
    if (expected->keyop(expected->ctx, got, &got_len,
                        expected->input, expected->input_len) <= 0) {
        t->err = "KEYOP_ERROR";
        goto err;
    }
    if (!memory_err_compare(t, "KEYOP_MISMATCH",
                            expected->output, expected->output_len,
                            got, got_len))
        goto err;

    t->err = NULL;
    OPENSSL_free(got);
    got = NULL;

    /* Repeat the test on a copy. */
    if (!TEST_ptr(copy = EVP_PKEY_CTX_dup(expected->ctx))) {
        t->err = "INTERNAL_ERROR";
        goto err;
    }
    if (expected->keyop(copy, NULL, &got_len, expected->input,
                        expected->input_len) <= 0
            || !TEST_ptr(got = OPENSSL_malloc(got_len))) {
        t->err = "KEYOP_LENGTH_ERROR";
        goto err;
    }
    if (expected->keyop(copy, got, &got_len, expected->input,
                        expected->input_len) <= 0) {
        t->err = "KEYOP_ERROR";
        goto err;
    }
    if (!memory_err_compare(t, "KEYOP_MISMATCH",
                            expected->output, expected->output_len,
                            got, got_len))
        goto err;

 err:
    OPENSSL_free(got);
    EVP_PKEY_CTX_free(copy);
    return 1;
}