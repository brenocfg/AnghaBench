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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_set_rsa_keygen_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_PKEY_RSA ; 
 int /*<<< orphan*/  EVP_PKEY_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  EVP_PKEY_keygen_init (int /*<<< orphan*/ *) ; 
 scalar_t__ TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/ *) ; 

EVP_PKEY *gen_rsa(void)
{
    EVP_PKEY_CTX *ctx = NULL;
    EVP_PKEY *pkey = NULL;

    (void)(TEST_ptr(ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL))
               && TEST_int_gt(EVP_PKEY_keygen_init(ctx), 0)
               && TEST_int_gt(EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048), 0)
               && TEST_int_gt(EVP_PKEY_keygen(ctx, &pkey), 0));
    EVP_PKEY_CTX_free(ctx);
    return pkey;
}