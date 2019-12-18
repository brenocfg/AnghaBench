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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CipherFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CipherUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int) ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int encrypt_decrypt(const EVP_CIPHER *cipher, const unsigned char *msg,
                           size_t len)
{
    int ret = 0, ctlen, ptlen;
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char key[128 / 8];
    unsigned char ct[64], pt[64];

    memset(key, 0, sizeof(key));
    if (!TEST_ptr(ctx = EVP_CIPHER_CTX_new())
            || !TEST_true(EVP_CipherInit_ex(ctx, cipher, NULL, key, NULL, 1))
            || !TEST_true(EVP_CipherUpdate(ctx, ct, &ctlen, msg, len))
            || !TEST_true(EVP_CipherFinal_ex(ctx, ct, &ctlen))
            || !TEST_true(EVP_CipherInit_ex(ctx, cipher, NULL, key, NULL, 0))
            || !TEST_true(EVP_CipherUpdate(ctx, pt, &ptlen, ct, ctlen))
            || !TEST_true(EVP_CipherFinal_ex(ctx, pt, &ptlen))
            || !TEST_mem_eq(pt, ptlen, msg, len))
        goto err;

    ret = 1;
err:
    EVP_CIPHER_CTX_free(ctx);
    return ret;
}