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
typedef  int /*<<< orphan*/  EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  KDF_F_KDF_TLS1_PRF_NEW ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OPENSSL_zalloc (int) ; 

__attribute__((used)) static EVP_KDF_IMPL *kdf_tls1_prf_new(void)
{
    EVP_KDF_IMPL *impl;

    if ((impl = OPENSSL_zalloc(sizeof(*impl))) == NULL)
        KDFerr(KDF_F_KDF_TLS1_PRF_NEW, ERR_R_MALLOC_FAILURE);
    return impl;
}