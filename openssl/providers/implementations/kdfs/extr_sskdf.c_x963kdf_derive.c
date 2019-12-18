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
struct TYPE_2__ {int /*<<< orphan*/  info_len; int /*<<< orphan*/  info; int /*<<< orphan*/  secret_len; int /*<<< orphan*/ * secret; int /*<<< orphan*/ * macctx; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_SSKDF ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROV_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  PROV_R_MISSING_SECRET ; 
 int /*<<< orphan*/  PROV_R_NOT_SUPPORTED ; 
 int SSKDF_hash_kdm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned char*,size_t) ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int x963kdf_derive(void *vctx, unsigned char *key, size_t keylen)
{
    KDF_SSKDF *ctx = (KDF_SSKDF *)vctx;
    const EVP_MD *md = ossl_prov_digest_md(&ctx->digest);

    if (ctx->secret == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SECRET);
        return 0;
    }

    if (ctx->macctx != NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_NOT_SUPPORTED);
        return 0;
    }

    /* H(x) = hash */
    if (md == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }

    return SSKDF_hash_kdm(md, ctx->secret, ctx->secret_len,
                          ctx->info, ctx->info_len, 1, key, keylen);
}