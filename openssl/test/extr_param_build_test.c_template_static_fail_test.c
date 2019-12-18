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
typedef  int /*<<< orphan*/  secure ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int OSSL_NELEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_param_bld_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_BN (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_uint (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_utf8_string (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_to_param_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned char*,int,unsigned char*,int) ; 

__attribute__((used)) static int template_static_fail_test(int n)
{
    unsigned char data[10000], secure[500];
    OSSL_PARAM_BLD bld;
    OSSL_PARAM prms[20];
    BIGNUM *bn = NULL;
    int res = 0;

    ossl_param_bld_init(&bld);
    if (!TEST_true(ossl_param_bld_push_uint(&bld, "i", 6))
        || !TEST_ptr(bn = (n & 1) == 0 ? BN_new() : BN_secure_new())
        || !TEST_true(BN_hex2bn(&bn, "ABCDEF78901234567890ABCDEF0987987654321"))
        || !TEST_true(ossl_param_bld_push_BN(&bld, "bn", bn))
        || !TEST_true(ossl_param_bld_push_utf8_string(&bld, "utf8_s", "abc",
                                                      1000))
        /* No OSSL_PARAMS */
        || !TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, NULL, 0, data,
                                                     sizeof(data), secure,
                                                     sizeof(secure)))
        /* Short OSSL_PARAMS */
        || !TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, prms, 2,
                                                     data, sizeof(data),
                                                     secure, sizeof(secure)))
        /* No normal data */
        || !TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, prms,
                                                     OSSL_NELEM(prms),
                                                     NULL, 0, secure,
                                                     sizeof(secure)))
        /* Not enough normal data */
        || !TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, prms,
                                                     OSSL_NELEM(prms),
                                                     data, 50, secure,
                                                     sizeof(secure))))
            goto err;
        if ((n & 1) == 1) {
            /* No secure data */
            if (!TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, prms,
                                                          OSSL_NELEM(prms),
                                                          data, sizeof(data),
                                                          NULL, 0))
            /* Not enough secure data */
            || !TEST_ptr_null(ossl_param_bld_to_param_ex(&bld, prms,
                                                         OSSL_NELEM(prms),
                                                         data, sizeof(data),
                                                         secure, 4)))
                goto err;
        }
    res = 1;
err:
    BN_free(bn);
    return res;
}