#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; scalar_t__ param_bin_len; int /*<<< orphan*/  param_bin; } ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int BIO_get_mem_data (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_int_gt (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_mem_eq (int /*<<< orphan*/ ,int,unsigned char*,int) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_KeyParams_bio (int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int i2d_KeyParams_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* pkey_params ; 

__attribute__((used)) static int params_bio_test(int id)
{
    int ret, out_len;
    BIO *in = NULL, *out = NULL;
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *in_key = NULL, *out_key = NULL;
    unsigned char *out_bin;
    int type = pkey_params[id].type;

    ret = TEST_ptr(ctx = EVP_PKEY_CTX_new_id(type, NULL))
        && TEST_ptr(in = BIO_new_mem_buf(pkey_params[id].param_bin,
                                        (int)pkey_params[id].param_bin_len))
        /* Load in pkey params from binary */
        && TEST_ptr(d2i_KeyParams_bio(type, &in_key, in))
        && TEST_ptr(out = BIO_new(BIO_s_mem()))
        /* Save pkey params to binary */
        && TEST_int_gt(i2d_KeyParams_bio(out, in_key), 0)
        /* test the output binary is the expected value */
        && TEST_int_gt(out_len = BIO_get_mem_data(out, &out_bin), 0)
        && TEST_mem_eq(pkey_params[id].param_bin,
                       (int)pkey_params[id].param_bin_len,
                       out_bin, out_len);

    BIO_free(in);
    BIO_free(out);
    EVP_PKEY_free(in_key);
    EVP_PKEY_free(out_key);
    EVP_PKEY_CTX_free(ctx);
    return ret;
}