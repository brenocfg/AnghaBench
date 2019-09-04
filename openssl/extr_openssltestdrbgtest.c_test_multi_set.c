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
typedef  int /*<<< orphan*/  RAND_DRBG ;

/* Variables and functions */
 int /*<<< orphan*/  NID_aes_192_ctr ; 
 int /*<<< orphan*/  NID_sha1 ; 
 int /*<<< orphan*/  NID_sha256 ; 
 int /*<<< orphan*/  RAND_DRBG_FLAG_HMAC ; 
 int /*<<< orphan*/  RAND_DRBG_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_instantiate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RAND_DRBG_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_crngt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uninstantiate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_multi_set(void)
{
    int rv = 0;
    RAND_DRBG *drbg = NULL;

    /* init drbg with default CTR initializer */
    if (!TEST_ptr(drbg = RAND_DRBG_new(0, 0, NULL))
        || !TEST_true(disable_crngt(drbg)))
        goto err;
    /* change it to use hmac */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_sha1, RAND_DRBG_FLAG_HMAC)))
        goto err;
    /* use same type */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_sha1, RAND_DRBG_FLAG_HMAC)))
        goto err;
    /* change it to use hash */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_sha256, 0)))
        goto err;
    /* use same type */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_sha256, 0)))
        goto err;
    /* change it to use ctr */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_aes_192_ctr, 0)))
        goto err;
    /* use same type */
    if (!TEST_true(RAND_DRBG_set(drbg, NID_aes_192_ctr, 0)))
        goto err;
    if (!TEST_int_gt(RAND_DRBG_instantiate(drbg, NULL, 0), 0))
        goto err;

    rv = 1;
err:
    uninstantiate(drbg);
    RAND_DRBG_free(drbg);
    return rv;
}