#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* err; TYPE_1__* data; } ;
struct TYPE_4__ {size_t output_len; int /*<<< orphan*/  output; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ PKEY_KDF_DATA ;
typedef  TYPE_2__ EVP_TEST ;

/* Variables and functions */
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ ,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  TEST_mem_eq (int /*<<< orphan*/ ,size_t,unsigned char*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (unsigned char*) ; 

__attribute__((used)) static int pkey_kdf_test_run(EVP_TEST *t)
{
    PKEY_KDF_DATA *expected = t->data;
    unsigned char *got = NULL;
    size_t got_len = expected->output_len;

    if (!TEST_ptr(got = OPENSSL_malloc(got_len))) {
        t->err = "INTERNAL_ERROR";
        goto err;
    }
    if (EVP_PKEY_derive(expected->ctx, got, &got_len) <= 0) {
        t->err = "KDF_DERIVE_ERROR";
        goto err;
    }
    if (!TEST_mem_eq(expected->output, expected->output_len, got, got_len)) {
        t->err = "KDF_MISMATCH";
        goto err;
    }
    t->err = NULL;

 err:
    OPENSSL_free(got);
    return 1;
}