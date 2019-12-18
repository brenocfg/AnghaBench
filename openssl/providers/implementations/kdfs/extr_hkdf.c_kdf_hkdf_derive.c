#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mode; int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  key_len; int /*<<< orphan*/ * key; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_HKDF ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  EVP_KDF_HKDF_MODE_EXPAND_ONLY 130 
#define  EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND 129 
#define  EVP_KDF_HKDF_MODE_EXTRACT_ONLY 128 
 int HKDF (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int HKDF_Expand (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int HKDF_Extract (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  PROV_R_MISSING_KEY ; 
 int /*<<< orphan*/  PROV_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int kdf_hkdf_derive(void *vctx, unsigned char *key, size_t keylen)
{
    KDF_HKDF *ctx = (KDF_HKDF *)vctx;
    const EVP_MD *md = ossl_prov_digest_md(&ctx->digest);

    if (md == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (ctx->key == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_KEY);
        return 0;
    }

    switch (ctx->mode) {
    case EVP_KDF_HKDF_MODE_EXTRACT_AND_EXPAND:
        return HKDF(md, ctx->salt, ctx->salt_len, ctx->key,
                    ctx->key_len, ctx->info, ctx->info_len, key,
                    keylen);

    case EVP_KDF_HKDF_MODE_EXTRACT_ONLY:
        return HKDF_Extract(md, ctx->salt, ctx->salt_len, ctx->key,
                            ctx->key_len, key, keylen);

    case EVP_KDF_HKDF_MODE_EXPAND_ONLY:
        return HKDF_Expand(md, ctx->key, ctx->key_len, ctx->info,
                           ctx->info_len, key, keylen);

    default:
        return 0;
    }
}