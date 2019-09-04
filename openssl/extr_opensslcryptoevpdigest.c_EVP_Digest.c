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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 scalar_t__ EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestUpdate (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_FLAG_ONESHOT ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int EVP_Digest(const void *data, size_t count,
               unsigned char *md, unsigned int *size, const EVP_MD *type,
               ENGINE *impl)
{
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    int ret;

    if (ctx == NULL)
        return 0;
    EVP_MD_CTX_set_flags(ctx, EVP_MD_CTX_FLAG_ONESHOT);
    ret = EVP_DigestInit_ex(ctx, type, impl)
        && EVP_DigestUpdate(ctx, data, count)
        && EVP_DigestFinal_ex(ctx, md, size);
    EVP_MD_CTX_free(ctx);

    return ret;
}