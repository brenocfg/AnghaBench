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
typedef  int /*<<< orphan*/  EVP_KDF_CTX ;
typedef  int /*<<< orphan*/  EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_KDF_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_KDF_fetch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_KDF_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EVP_KDF_CTX *get_kdfbyname(const char *name)
{
    EVP_KDF *kdf = EVP_KDF_fetch(NULL, name, NULL);
    EVP_KDF_CTX *kctx = EVP_KDF_CTX_new(kdf);

    EVP_KDF_free(kdf);
    return kctx;
}