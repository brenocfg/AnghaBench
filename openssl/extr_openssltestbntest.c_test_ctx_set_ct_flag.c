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
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t OSSL_NELEM (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_ctx_set_ct_flag(BN_CTX *c)
{
    int st = 0;
    size_t i;
    BIGNUM *b[15];

    BN_CTX_start(c);
    for (i = 0; i < OSSL_NELEM(b); i++) {
        if (!TEST_ptr(b[i] = BN_CTX_get(c)))
            goto err;
        if (i % 2 == 1)
            BN_set_flags(b[i], BN_FLG_CONSTTIME);
    }

    st = 1;
 err:
    BN_CTX_end(c);
    return st;
}