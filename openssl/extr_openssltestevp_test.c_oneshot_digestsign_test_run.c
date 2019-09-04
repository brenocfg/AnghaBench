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
struct TYPE_6__ {int /*<<< orphan*/  output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  osin_len; int /*<<< orphan*/  osin; int /*<<< orphan*/  ctx; } ;
struct TYPE_5__ {char* err; TYPE_2__* data; } ;
typedef  TYPE_1__ EVP_TEST ;
typedef  TYPE_2__ DIGESTSIGN_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestSign (int /*<<< orphan*/ ,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 
 int /*<<< orphan*/  memory_err_compare (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int oneshot_digestsign_test_run(EVP_TEST *t)
{
    DIGESTSIGN_DATA *expected = t->data;
    unsigned char *got = NULL;
    size_t got_len;

    if (!EVP_DigestSign(expected->ctx, NULL, &got_len,
                        expected->osin, expected->osin_len)) {
        t->err = "DIGESTSIGN_LENGTH_ERROR";
        goto err;
    }
    if (!TEST_ptr(got = OPENSSL_malloc(got_len))) {
        t->err = "MALLOC_FAILURE";
        goto err;
    }
    if (!EVP_DigestSign(expected->ctx, got, &got_len,
                        expected->osin, expected->osin_len)) {
        t->err = "DIGESTSIGN_ERROR";
        goto err;
    }
    if (!memory_err_compare(t, "SIGNATURE_MISMATCH",
                            expected->output, expected->output_len,
                            got, got_len))
        goto err;

    t->err = NULL;
 err:
    OPENSSL_free(got);
    return 1;
}