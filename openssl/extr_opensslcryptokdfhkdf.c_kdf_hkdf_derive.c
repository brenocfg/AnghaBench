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
struct TYPE_3__ {int mode; int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/ * md; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; } ;
typedef  TYPE_1__ EVP_KDF_IMPL ;

/* Variables and functions */
#define  EVP_KDF_HKDF_MODE_EXPAND_ONLY 130 
#define  EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND 129 
#define  EVP_KDF_HKDF_MODE_EXTRACT_ONLY 128 
 int HKDF (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int HKDF_Expand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int HKDF_Extract (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  KDF_F_KDF_HKDF_DERIVE ; 
 int /*<<< orphan*/  KDF_R_MISSING_KEY ; 
 int /*<<< orphan*/  KDF_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  KDFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kdf_hkdf_derive(EVP_KDF_IMPL *impl, unsigned char *key,
                           size_t keylen)
{
    if (impl->md == NULL) {
        KDFerr(KDF_F_KDF_HKDF_DERIVE, KDF_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (impl->key == NULL) {
        KDFerr(KDF_F_KDF_HKDF_DERIVE, KDF_R_MISSING_KEY);
        return 0;
    }

    switch (impl->mode) {
    case EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND:
        return HKDF(impl->md, impl->salt, impl->salt_len, impl->key,
                    impl->key_len, impl->info, impl->info_len, key,
                    keylen);

    case EVP_KDF_HKDF_MODE_EXTRACT_ONLY:
        return HKDF_Extract(impl->md, impl->salt, impl->salt_len, impl->key,
                            impl->key_len, key, keylen);

    case EVP_KDF_HKDF_MODE_EXPAND_ONLY:
        return HKDF_Expand(impl->md, impl->key, impl->key_len, impl->info,
                           impl->info_len, key, keylen);

    default:
        return 0;
    }
}