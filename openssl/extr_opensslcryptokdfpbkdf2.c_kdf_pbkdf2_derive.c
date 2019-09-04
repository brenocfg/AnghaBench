#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  md; int /*<<< orphan*/  iter; int /*<<< orphan*/  salt_len; int /*<<< orphan*/ * salt; int /*<<< orphan*/  pass_len; int /*<<< orphan*/ * pass; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
 int /*<<< orphan*/  KDF_F_KDF_PBKDF2_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_PASS ; 
 int /*<<< orphan*/  KDF_R_MISSING_SALT ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pkcs5_pbkdf2_alg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int kdf_pbkdf2_derive(EVP_KDF_IMPL *impl, unsigned char *key,
                             size_t keylen)
{
    if (impl->pass == NULL) {
        KDFerr(KDF_F_KDF_PBKDF2_DERIVE, KDF_R_MISSING_PASS);
        return 0;
    }

    if (impl->salt == NULL) {
        KDFerr(KDF_F_KDF_PBKDF2_DERIVE, KDF_R_MISSING_SALT);
        return 0;
    }

    return pkcs5_pbkdf2_alg((char *)impl->pass, impl->pass_len,
                            impl->salt, impl->salt_len, impl->iter,
                            impl->md, key, keylen);
}