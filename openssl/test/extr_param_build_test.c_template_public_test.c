#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_23__ {char const* key; char const* data; int /*<<< orphan*/  data_type; int /*<<< orphan*/  data_size; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_cmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 TYPE_1__* BN_new () ; 
 int /*<<< orphan*/  BN_set_word (TYPE_1__*,int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  OSSL_PARAM_INTEGER ; 
 int /*<<< orphan*/  OSSL_PARAM_REAL ; 
 int /*<<< orphan*/  OSSL_PARAM_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  OSSL_PARAM_get_BN (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_double (TYPE_1__*,double*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int32 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int64 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_long (TYPE_1__*,long*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_ptr (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_string (TYPE_1__*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__* OSSL_PARAM_locate (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TEST_double_eq (double,double) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_long_eq (long,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_str_eq (char const*,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_param_bld_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_param_bld_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_BN (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_param_bld_push_double (int /*<<< orphan*/ *,char*,double) ; 
 int /*<<< orphan*/  ossl_param_bld_push_int (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_int64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_long (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_utf8_ptr (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ossl_param_bld_push_utf8_string (int /*<<< orphan*/ *,char*,char*,int) ; 
 TYPE_1__* ossl_param_bld_to_param (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int template_public_test(void)
{
    OSSL_PARAM_BLD bld;
    OSSL_PARAM *params = NULL, *p;
    BIGNUM *bn = NULL, *bn_res = NULL;
    int i;
    long int l;
    int32_t i32;
    int64_t i64;
    double d;
    char *utf = NULL;
    const char *cutf;
    int res = 0;

    ossl_param_bld_init(&bld);
    if (!TEST_true(ossl_param_bld_push_int(&bld, "i", -6))
        || !TEST_true(ossl_param_bld_push_long(&bld, "l", 42))
        || !TEST_true(ossl_param_bld_push_int32(&bld, "i32", 1532))
        || !TEST_true(ossl_param_bld_push_int64(&bld, "i64", -9999999))
        || !TEST_true(ossl_param_bld_push_double(&bld, "d", 1.61803398875))
        || !TEST_ptr(bn = BN_new())
        || !TEST_true(BN_set_word(bn, 1729))
        || !TEST_true(ossl_param_bld_push_BN(&bld, "bignumber", bn))
        || !TEST_true(ossl_param_bld_push_utf8_string(&bld, "utf8_s", "foo",
                                                      sizeof("foo")))
        || !TEST_true(ossl_param_bld_push_utf8_ptr(&bld, "utf8_p", "bar-boom",
                                                   0))
        || !TEST_ptr(params = ossl_param_bld_to_param(&bld))
        /* Check int */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i"))
        || !TEST_true(OSSL_PARAM_get_int(p, &i))
        || !TEST_str_eq(p->key, "i")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int))
        || !TEST_int_eq(i, -6)
        /* Check int32 */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i32"))
        || !TEST_true(OSSL_PARAM_get_int32(p, &i32))
        || !TEST_str_eq(p->key, "i32")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int32_t))
        || !TEST_int_eq((int)i32, 1532)
        /* Check int64 */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i64"))
        || !TEST_str_eq(p->key, "i64")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int64_t))
        || !TEST_true(OSSL_PARAM_get_int64(p, &i64))
        || !TEST_long_eq((long)i64, -9999999)
        /* Check long */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "l"))
        || !TEST_str_eq(p->key, "l")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(long int))
        || !TEST_true(OSSL_PARAM_get_long(p, &l))
        || !TEST_long_eq(l, 42)
        /* Check double */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "d"))
        || !TEST_true(OSSL_PARAM_get_double(p, &d))
        || !TEST_str_eq(p->key, "d")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_REAL)
        || !TEST_size_t_eq(p->data_size, sizeof(double))
        || !TEST_double_eq(d, 1.61803398875)
        /* Check UTF8 string */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "utf8_s"))
        || !TEST_str_eq(p->data, "foo")
        || !TEST_true(OSSL_PARAM_get_utf8_string(p, &utf, 0))
        || !TEST_str_eq(utf, "foo")
        /* Check UTF8 pointer */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "utf8_p"))
        || !TEST_true(OSSL_PARAM_get_utf8_ptr(p, &cutf))
        || !TEST_str_eq(cutf, "bar-boom")
        /* Check BN */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "bignumber"))
        || !TEST_str_eq(p->key, "bignumber")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_true(OSSL_PARAM_get_BN(p, &bn_res))
        || !TEST_int_eq(BN_cmp(bn_res, bn), 0))
        goto err;
    res = 1;
err:
    ossl_param_bld_free(params);
    OPENSSL_free(utf);
    BN_free(bn);
    BN_free(bn_res);
    return res;
}