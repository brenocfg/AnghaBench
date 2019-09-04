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
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EVP_DigestUpdate (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int SHA256_DIGEST_LENGTH ; 
 int /*<<< orphan*/  TEST_mem_eq (unsigned char*,int,unsigned char const*,int) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int) ; 

__attribute__((used)) static int calculate_digest(const EVP_MD *md, const char *msg, size_t len,
                            const unsigned char *exptd)
{
    unsigned char out[SHA256_DIGEST_LENGTH];
    EVP_MD_CTX *ctx;
    int ret = 0;

    if (!TEST_ptr(ctx = EVP_MD_CTX_new())
            || !TEST_true(EVP_DigestInit_ex(ctx, md, NULL))
            || !TEST_true(EVP_DigestUpdate(ctx, msg, len))
            || !TEST_true(EVP_DigestFinal_ex(ctx, out, NULL))
            || !TEST_mem_eq(out, SHA256_DIGEST_LENGTH, exptd,
                            SHA256_DIGEST_LENGTH)
            || !TEST_true(md == EVP_MD_CTX_md(ctx)))
        goto err;

    ret = 1;
 err:
    EVP_MD_CTX_free(ctx);
    return ret;
}