#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  data2 ;
typedef  int /*<<< orphan*/  data1 ;
struct TYPE_21__ {unsigned int data_type; size_t data_size; void* data; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM_BLD ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_cmp (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 TYPE_1__* BN_secure_new () ; 
 int /*<<< orphan*/  BN_set_word (TYPE_1__*,int) ; 
 int OSSL_PARAM_OCTET_PTR ; 
 int OSSL_PARAM_OCTET_STRING ; 
 int OSSL_PARAM_UNSIGNED_INTEGER ; 
 int /*<<< orphan*/  OSSL_PARAM_get_BN (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_size_t (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint (TYPE_1__*,unsigned int*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint32 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint64 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_ulong (TYPE_1__*,unsigned long*) ; 
 TYPE_1__* OSSL_PARAM_locate (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_mem_eq (void*,size_t,...) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_str_eq (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_uint_eq (unsigned int,int) ; 
 int /*<<< orphan*/  TEST_ulong_eq (unsigned long,int) ; 
 int /*<<< orphan*/  ossl_param_bld_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_param_bld_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_param_bld_push_BN (int /*<<< orphan*/ *,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_param_bld_push_octet_ptr (int /*<<< orphan*/ *,char*,unsigned char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_octet_string (int /*<<< orphan*/ *,char*,int*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_size_t (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_uint (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_uint32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_uint64 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ossl_param_bld_push_ulong (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__* ossl_param_bld_to_param (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int template_private_test(void)
{
    static int data1[] = { 2, 3, 5, 7, 11, 15, 17 };
    static unsigned char data2[] = { 2, 4, 6, 8, 10 };
    OSSL_PARAM_BLD bld;
    OSSL_PARAM *params = NULL, *p;
    unsigned int i;
    unsigned long int l;
    uint32_t i32;
    uint64_t i64;
    size_t st;
    BIGNUM *bn = NULL, *bn_res = NULL;
    int res = 0;

    ossl_param_bld_init(&bld);
    if (!TEST_true(ossl_param_bld_push_uint(&bld, "i", 6))
        || !TEST_true(ossl_param_bld_push_ulong(&bld, "l", 42))
        || !TEST_true(ossl_param_bld_push_uint32(&bld, "i32", 1532))
        || !TEST_true(ossl_param_bld_push_uint64(&bld, "i64", 9999999))
        || !TEST_true(ossl_param_bld_push_size_t(&bld, "st", 65537))
        || !TEST_ptr(bn = BN_secure_new())
        || !TEST_true(BN_set_word(bn, 1729))
        || !TEST_true(ossl_param_bld_push_BN(&bld, "bignumber", bn))
        || !TEST_true(ossl_param_bld_push_octet_string(&bld, "oct_s", data1,
                                                       sizeof(data1)))
        || !TEST_true(ossl_param_bld_push_octet_ptr(&bld, "oct_p", data2,
                                                    sizeof(data2)))
        || !TEST_ptr(params = ossl_param_bld_to_param(&bld))
        /* Check unsigned int */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i"))
        || !TEST_true(OSSL_PARAM_get_uint(p, &i))
        || !TEST_str_eq(p->key, "i")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int))
        || !TEST_uint_eq(i, 6)
        /* Check unsigned int32 */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i32"))
        || !TEST_true(OSSL_PARAM_get_uint32(p, &i32))
        || !TEST_str_eq(p->key, "i32")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int32_t))
        || !TEST_uint_eq((unsigned int)i32, 1532)
        /* Check unsigned int64 */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "i64"))
        || !TEST_str_eq(p->key, "i64")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(int64_t))
        || !TEST_true(OSSL_PARAM_get_uint64(p, &i64))
        || !TEST_ulong_eq((unsigned long)i64, 9999999)
        /* Check unsigned long int */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "l"))
        || !TEST_str_eq(p->key, "l")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(unsigned long int))
        || !TEST_true(OSSL_PARAM_get_ulong(p, &l))
        || !TEST_ulong_eq(l, 42)
        /* Check size_t */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "st"))
        || !TEST_str_eq(p->key, "st")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_UNSIGNED_INTEGER)
        || !TEST_size_t_eq(p->data_size, sizeof(size_t))
        || !TEST_true(OSSL_PARAM_get_size_t(p, &st))
        || !TEST_size_t_eq(st, 65537)
        /* Check octet string */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "oct_s"))
        || !TEST_str_eq(p->key, "oct_s")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_OCTET_STRING)
        || !TEST_mem_eq(p->data, p->data_size, data1, sizeof(data1))
        /* Check octet pointer */
        || !TEST_ptr(p = OSSL_PARAM_locate(params, "oct_p"))
        || !TEST_str_eq(p->key, "oct_p")
        || !TEST_uint_eq(p->data_type, OSSL_PARAM_OCTET_PTR)
        || !TEST_mem_eq(*(void **)p->data, p->data_size, data2, sizeof(data2))
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
    BN_free(bn);
    BN_free(bn_res);
    return res;
}