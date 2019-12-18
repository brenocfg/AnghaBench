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
typedef  int /*<<< orphan*/  const EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  EVP_EncryptInit_ex (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_aes_192_gcm () ; 
 scalar_t__ TEST_false (int /*<<< orphan*/ ) ; 
 scalar_t__ TEST_ptr (int /*<<< orphan*/  const*) ; 
 scalar_t__ TEST_true (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int badkeylen_test(void)
{
    int ret;
    EVP_CIPHER_CTX *ctx = NULL;
    const EVP_CIPHER *cipher;

    ret = TEST_ptr(cipher = EVP_aes_192_gcm())
          && TEST_ptr(ctx = EVP_CIPHER_CTX_new())
          && TEST_true(EVP_EncryptInit_ex(ctx, cipher, NULL, NULL, NULL))
          && TEST_false(EVP_CIPHER_CTX_set_key_length(ctx, 2));
    EVP_CIPHER_CTX_free(ctx);
    return ret;
}