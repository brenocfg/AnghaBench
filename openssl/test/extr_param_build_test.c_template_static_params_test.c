#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  secure ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_19__ {char* key; unsigned int data_type; char* data; int /*<<< orphan*/  data_size; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 scalar_t__ BN_get_word (TYPE_1__*) ; 
 TYPE_1__* BN_new () ; 
 TYPE_1__* BN_secure_new () ; 
 int /*<<< orphan*/  BN_set_word (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OSSL_NELEM (TYPE_1__*) ; 
 int OSSL_PARAM_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  OSSL_PARAM_get_BN (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_string (TYPE_1__*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* OSSL_PARAM_locate (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_size_t_le (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (unsigned int,int) ; 
 int /*<<< orphan*/  ossl_param_bld_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_BN (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_param_bld_push_uint (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_utf8_string (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ossl_param_bld_to_param_ex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,unsigned char*,int,unsigned char*,int) ; 

__attribute__((used)) static int template_static_params_test(int n)
{
    unsigned char data[1000], secure[500];
    OSSL_PARAM_BLD bld;
    OSSL_PARAM params[20], *p;
    BIGNUM *bn = NULL, *bn_r = NULL;
    unsigned int i;
    char *utf = NULL;
    int res = 0;

    ossl_param_bld_init(&bld);
    if (!TEST_true(ossl_param_bld_push_uint(&bld, "i", 6))
        || !TEST_ptr(bn = (n & 1) == 0 ? BN_new() : BN_secure_new())
        || !TEST_true(BN_set_word(bn, 1337))
        || !TEST_true(ossl_param_bld_push_BN(&bld, "bn", bn))
        || !TEST_true(ossl_param_bld_push_utf8_string(&bld, "utf8_s", "bar",
                                                      0))
        || !TEST_ptr(ossl_param_bld_to_param_ex(&bld, params,
                                                OSSL_NELEM(params),
                                                data, sizeof(data),
                                                secure, sizeof(secure)))
        /* Check unsigned int */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i"))
        || !TEST_true(OSSL_PARAM_get_uint(p, &i))
        || !TEST_str_eq(p->key, "i")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int))
        || !TEST_uint_eq(i, 6)
        /* Check BIGNUM */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "bn"))
        || !TEST_true(OSSL_PARAM_get_BN(p, &bn_r))
        || !TEST_str_eq(p->key, "bn")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_le(p->data_size, sizeof(BN_ULONG))
        || !TEST_uint_eq((unsigned int)BN_get_word(bn_r), 1337)
        /* Check UTF8 string */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "utf8_s"))
        || !TEST_str_eq(p->data, "bar")
        || !TEST_true(OSSL_PARAM_get_utf8_string(p, &utf, 0))
        || !TEST_str_eq(utf, "bar"))
        goto err;
    res = 1;
err:
    OPENSSL_free(utf);
    BN_free(bn);
    BN_free(bn_r);
    return res;
}