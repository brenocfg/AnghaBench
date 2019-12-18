#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {unsigned char* kder; size_t size; int evptype; int check; int pub_check; int param_check; int type; } ;
struct TYPE_27__ {struct TYPE_27__* pkey; } ;
typedef  TYPE_1__ EVP_PKEY_CTX ;
typedef  TYPE_1__ EVP_PKEY ;
typedef  TYPE_1__ EC_KEY ;
typedef  TYPE_1__ BIO ;
typedef  TYPE_5__ APK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (TYPE_1__*) ; 
 TYPE_1__* BIO_new_mem_buf (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (TYPE_1__*) ; 
 TYPE_1__* EVP_PKEY_CTX_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_assign_EC_KEY (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_check (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_id (TYPE_1__*) ; 
 TYPE_1__* EVP_PKEY_new () ; 
 int /*<<< orphan*/  EVP_PKEY_param_check (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_public_check (TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_up_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  TEST_ptr_eq (unsigned char const*,unsigned char const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* d2i_AutoPrivateKey (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 TYPE_1__* d2i_ECParameters (int /*<<< orphan*/ *,unsigned char const**,size_t) ; 
 TYPE_1__* d2i_EC_PUBKEY_bio (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* keycheckdata ; 

__attribute__((used)) static int test_EVP_PKEY_check(int i)
{
    int ret = 0;
    const unsigned char *p;
    EVP_PKEY *pkey = NULL;
#ifndef OPENSSL_NO_EC
    EC_KEY *eckey = NULL;
#endif
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY_CTX *ctx2 = NULL;
    const APK_DATA *ak = &keycheckdata[i];
    const unsigned char *input = ak->kder;
    size_t input_len = ak->size;
    int expected_id = ak->evptype;
    int expected_check = ak->check;
    int expected_pub_check = ak->pub_check;
    int expected_param_check = ak->param_check;
    int type = ak->type;
    BIO *pubkey = NULL;

    p = input;

    switch (type) {
    case 0:
        if (!TEST_ptr(pkey = d2i_AutoPrivateKey(NULL, &p, input_len))
            || !TEST_ptr_eq(p, input + input_len)
            || !TEST_int_eq(EVP_PKEY_id(pkey), expected_id))
            goto done;
        break;
#ifndef OPENSSL_NO_EC
    case 1:
        if (!TEST_ptr(pubkey = BIO_new_mem_buf(input, input_len))
            || !TEST_ptr(eckey = d2i_EC_PUBKEY_bio(pubkey, NULL))
            || !TEST_ptr(pkey = EVP_PKEY_new())
            || !TEST_true(EVP_PKEY_assign_EC_KEY(pkey, eckey)))
            goto done;
        break;
    case 2:
        if (!TEST_ptr(eckey = d2i_ECParameters(NULL, &p, input_len))
            || !TEST_ptr_eq(p, input + input_len)
            || !TEST_ptr(pkey = EVP_PKEY_new())
            || !TEST_true(EVP_PKEY_assign_EC_KEY(pkey, eckey)))
            goto done;
        break;
#endif
    default:
        return 0;
    }

    if (!TEST_ptr(ctx = EVP_PKEY_CTX_new(pkey, NULL)))
        goto done;

    if (!TEST_int_eq(EVP_PKEY_check(ctx), expected_check))
        goto done;

    if (!TEST_int_eq(EVP_PKEY_public_check(ctx), expected_pub_check))
        goto done;

    if (!TEST_int_eq(EVP_PKEY_param_check(ctx), expected_param_check))
        goto done;

    ctx2 = EVP_PKEY_CTX_new_id(0xdefaced, NULL);
    /* assign the pkey directly, as an internal test */
    EVP_PKEY_up_ref(pkey);
    ctx2->pkey = pkey;

    if (!TEST_int_eq(EVP_PKEY_check(ctx2), 0xbeef))
        goto done;

    if (!TEST_int_eq(EVP_PKEY_public_check(ctx2), 0xbeef))
        goto done;

    if (!TEST_int_eq(EVP_PKEY_param_check(ctx2), 0xbeef))
        goto done;

    ret = 1;

 done:
    EVP_PKEY_CTX_free(ctx);
    EVP_PKEY_CTX_free(ctx2);
    EVP_PKEY_free(pkey);
    BIO_free(pubkey);
    return ret;
}