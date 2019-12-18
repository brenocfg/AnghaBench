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

/* Variables and functions */
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_sha1 () ; 

__attribute__((used)) static int derive_pvk_key(unsigned char *key,
                          const unsigned char *salt, unsigned int saltlen,
                          const unsigned char *pass, int passlen)
{
    EVP_MD_CTX *mctx = EVP_MD_CTX_new();
    int rv = 1;
    if (mctx == NULL
        || !EVP_DigestInit_ex(mctx, EVP_sha1(), NULL)
        || !EVP_DigestUpdate(mctx, salt, saltlen)
        || !EVP_DigestUpdate(mctx, pass, passlen)
        || !EVP_DigestFinal_ex(mctx, key, NULL))
        rv = 0;

    EVP_MD_CTX_free(mctx);
    return rv;
}