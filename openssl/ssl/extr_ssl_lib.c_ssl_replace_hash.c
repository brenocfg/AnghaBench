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
 scalar_t__ EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  ssl_clear_hash_ctx (int /*<<< orphan*/ **) ; 

EVP_MD_CTX *ssl_replace_hash(EVP_MD_CTX **hash, const EVP_MD *md)
{
    ssl_clear_hash_ctx(hash);
    *hash = EVP_MD_CTX_new();
    if (*hash == NULL || (md && EVP_DigestInit_ex(*hash, md, NULL) <= 0)) {
        EVP_MD_CTX_free(*hash);
        *hash = NULL;
        return NULL;
    }
    return *hash;
}