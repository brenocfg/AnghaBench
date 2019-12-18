#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ul ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ubuf ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bn_val ;
struct TYPE_45__ {size_t data_size; int return_size; } ;
typedef  TYPE_1__ OSSL_PARAM ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 TYPE_1__* BN_lebin2bn (unsigned char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (void*) ; 
 size_t OSSL_NELEM (char const**) ; 
 TYPE_1__ OSSL_PARAM_construct_BN (char*,unsigned char*,int) ; 
 TYPE_1__ OSSL_PARAM_construct_double (char*,double*) ; 
 TYPE_1__ OSSL_PARAM_construct_end () ; 
 TYPE_1__ OSSL_PARAM_construct_int (char*,int*) ; 
 TYPE_1__ OSSL_PARAM_construct_int32 (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ OSSL_PARAM_construct_int64 (char*,scalar_t__*) ; 
 TYPE_1__ OSSL_PARAM_construct_long (char*,long*) ; 
 TYPE_1__ OSSL_PARAM_construct_octet_ptr (char*,void**,int /*<<< orphan*/ ) ; 
 TYPE_1__ OSSL_PARAM_construct_octet_string (char*,char*,int) ; 
 TYPE_1__ OSSL_PARAM_construct_size_t (char*,size_t*) ; 
 TYPE_1__ OSSL_PARAM_construct_uint (char*,unsigned int*) ; 
 TYPE_1__ OSSL_PARAM_construct_uint32 (char*,int /*<<< orphan*/ *) ; 
 TYPE_1__ OSSL_PARAM_construct_uint64 (char*,scalar_t__*) ; 
 TYPE_1__ OSSL_PARAM_construct_ulong (char*,unsigned long*) ; 
 TYPE_1__ OSSL_PARAM_construct_utf8_ptr (char*,char**,int /*<<< orphan*/ ) ; 
 TYPE_1__ OSSL_PARAM_construct_utf8_string (char*,char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_BN (TYPE_1__*,TYPE_1__**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_double (TYPE_1__*,double*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_int64 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_octet_ptr (TYPE_1__*,void const**,size_t*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_octet_string (TYPE_1__*,void**,int,size_t*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_uint64 (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_ptr (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  OSSL_PARAM_get_utf8_string (TYPE_1__*,char**,int) ; 
 TYPE_1__* OSSL_PARAM_locate (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_BN (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_double (TYPE_1__*,double) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_int32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_octet_ptr (TYPE_1__*,unsigned long*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_octet_string (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_uint32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_utf8_ptr (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  OSSL_PARAM_set_utf8_string (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  TEST_BN_eq (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_double_eq (double,double) ; 
 int /*<<< orphan*/  TEST_mem_eq (void*,int,char*,int) ; 
 int /*<<< orphan*/  TEST_note (char*,size_t,char const*) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (void*,void*) ; 
 int /*<<< orphan*/  TEST_ptr_null (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_size_t_eq (size_t,int) ; 
 int /*<<< orphan*/  TEST_str_eq (char*,char*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_param_construct(void)
{
    static const char *int_names[] = {
        "int", "long", "int32", "int64"
    };
    static const char *uint_names[] = {
        "uint", "ulong", "uint32", "uint64", "size_t"
    };
    static const unsigned char bn_val[16] = {
        0xac, 0x75, 0x22, 0x7d, 0x81, 0x06, 0x7a, 0x23,
        0xa6, 0xed, 0x87, 0xc7, 0xab, 0xf4, 0x73, 0x22
    };
    OSSL_PARAM params[20];
    char buf[100], buf2[100], *bufp, *bufp2;
    unsigned char ubuf[100];
    void *vp, *vpn = NULL, *vp2;
    OSSL_PARAM *cp;
    int i, n = 0, ret = 0;
    unsigned int u;
    long int l;
    unsigned long int ul;
    int32_t i32;
    uint32_t u32;
    int64_t i64;
    uint64_t u64;
    size_t j, k, s;
    double d, d2;
    BIGNUM *bn = NULL, *bn2 = NULL;

    params[n++] = OSSL_PARAM_construct_int("int", &i);
    params[n++] = OSSL_PARAM_construct_uint("uint", &u);
    params[n++] = OSSL_PARAM_construct_long("long", &l);
    params[n++] = OSSL_PARAM_construct_ulong("ulong", &ul);
    params[n++] = OSSL_PARAM_construct_int32("int32", &i32);
    params[n++] = OSSL_PARAM_construct_int64("int64", &i64);
    params[n++] = OSSL_PARAM_construct_uint32("uint32", &u32);
    params[n++] = OSSL_PARAM_construct_uint64("uint64", &u64);
    params[n++] = OSSL_PARAM_construct_size_t("size_t", &s);
    params[n++] = OSSL_PARAM_construct_double("double", &d);
    params[n++] = OSSL_PARAM_construct_BN("bignum", ubuf, sizeof(ubuf));
    params[n++] = OSSL_PARAM_construct_utf8_string("utf8str", buf, sizeof(buf));
    params[n++] = OSSL_PARAM_construct_octet_string("octstr", buf, sizeof(buf));
    params[n++] = OSSL_PARAM_construct_utf8_ptr("utf8ptr", &bufp, 0);
    params[n++] = OSSL_PARAM_construct_octet_ptr("octptr", &vp, 0);
    params[n] = OSSL_PARAM_construct_end();

    /* Search failure */
    if (!TEST_ptr_null(OSSL_PARAM_locate(params, "fnord")))
        goto err;

    /* All signed integral types */
    for (j = 0; j < OSSL_NELEM(int_names); j++) {
        if (!TEST_ptr(cp = OSSL_PARAM_locate(params, int_names[j]))
            || !TEST_true(OSSL_PARAM_set_int32(cp, (int32_t)(3 + j)))
            || !TEST_true(OSSL_PARAM_get_int64(cp, &i64))
            || !TEST_size_t_eq(cp->data_size, cp->return_size)
            || !TEST_size_t_eq((size_t)i64, 3 + j)) {
            TEST_note("iteration %zu var %s", j + 1, int_names[j]);
            goto err;
        }
    }
    /* All unsigned integral types */
    for (j = 0; j < OSSL_NELEM(uint_names); j++) {
        if (!TEST_ptr(cp = OSSL_PARAM_locate(params, uint_names[j]))
            || !TEST_true(OSSL_PARAM_set_uint32(cp, (uint32_t)(3 + j)))
            || !TEST_true(OSSL_PARAM_get_uint64(cp, &u64))
            || !TEST_size_t_eq(cp->data_size, cp->return_size)
            || !TEST_size_t_eq((size_t)u64, 3 + j)) {
            TEST_note("iteration %zu var %s", j + 1, uint_names[j]);
            goto err;
        }
    }
    /* Real */
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "double"))
        || !TEST_true(OSSL_PARAM_set_double(cp, 3.14))
        || !TEST_true(OSSL_PARAM_get_double(cp, &d2))
        || !TEST_size_t_eq(cp->return_size, sizeof(double))
        || !TEST_double_eq(d, d2))
        goto err;
    /* UTF8 string */
    bufp = NULL;
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "utf8str"))
        || !TEST_true(OSSL_PARAM_set_utf8_string(cp, "abcdef"))
        || !TEST_size_t_eq(cp->return_size, sizeof("abcdef"))
        || !TEST_true(OSSL_PARAM_get_utf8_string(cp, &bufp, 0))
        || !TEST_str_eq(bufp, "abcdef"))
        goto err;
    OPENSSL_free(bufp);
    bufp = buf2;
    if (!TEST_true(OSSL_PARAM_get_utf8_string(cp, &bufp, sizeof(buf2)))
        || !TEST_str_eq(buf2, "abcdef"))
        goto err;
    /* UTF8 pointer */
    bufp = buf;
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "utf8ptr"))
        || !TEST_true(OSSL_PARAM_set_utf8_ptr(cp, "tuvwxyz"))
        || !TEST_size_t_eq(cp->return_size, sizeof("tuvwxyz"))
        || !TEST_str_eq(bufp, "tuvwxyz")
        || !TEST_true(OSSL_PARAM_get_utf8_ptr(cp, (const char **)&bufp2))
        || !TEST_ptr_eq(bufp2, bufp))
        goto err;
    /* OCTET string */
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "octstr"))
        || !TEST_true(OSSL_PARAM_set_octet_string(cp, "abcdefghi",
                                                  sizeof("abcdefghi")))
        || !TEST_size_t_eq(cp->return_size, sizeof("abcdefghi")))
        goto err;
    /* Match the return size to avoid trailing garbage bytes */
    cp->data_size = cp->return_size;
    if (!TEST_true(OSSL_PARAM_get_octet_string(cp, &vpn, 0, &s))
        || !TEST_size_t_eq(s, sizeof("abcdefghi"))
        || !TEST_mem_eq(vpn, sizeof("abcdefghi"),
                        "abcdefghi", sizeof("abcdefghi")))
        goto err;
    vp = buf2;
    if (!TEST_true(OSSL_PARAM_get_octet_string(cp, &vp, sizeof(buf2), &s))
        || !TEST_size_t_eq(s, sizeof("abcdefghi"))
        || !TEST_mem_eq(vp, sizeof("abcdefghi"),
                        "abcdefghi", sizeof("abcdefghi")))
        goto err;
    /* OCTET pointer */
    vp = &l;
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "octptr"))
        || !TEST_true(OSSL_PARAM_set_octet_ptr(cp, &ul, sizeof(ul)))
        || !TEST_size_t_eq(cp->return_size, sizeof(ul))
        || !TEST_ptr_eq(vp, &ul))
        goto err;
    /* Match the return size to avoid trailing garbage bytes */
    cp->data_size = cp->return_size;
    if (!TEST_true(OSSL_PARAM_get_octet_ptr(cp, (const void **)&vp2, &k))
        || !TEST_size_t_eq(k, sizeof(ul))
        || !TEST_ptr_eq(vp2, vp))
        goto err;
    /* BIGNUM */
    if (!TEST_ptr(cp = OSSL_PARAM_locate(params, "bignum"))
        || !TEST_ptr(bn = BN_lebin2bn(bn_val, (int)sizeof(bn_val), NULL))
        || !TEST_true(OSSL_PARAM_set_BN(cp, bn))
        || !TEST_size_t_eq(cp->data_size, cp->return_size))
        goto err;
    /* Match the return size to avoid trailing garbage bytes */
    cp->data_size = cp->return_size;
    if(!TEST_true(OSSL_PARAM_get_BN(cp, &bn2))
        || !TEST_BN_eq(bn, bn2))
        goto err;
    ret = 1;
err:
    OPENSSL_free(vpn);
    BN_free(bn);
    BN_free(bn2);
    return ret;
}