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
struct TYPE_2__ {scalar_t__ cek_nid; scalar_t__ ukm_len; size_t dkm_len; int /*<<< orphan*/  secret_len; int /*<<< orphan*/ * secret; int /*<<< orphan*/ * ukm; int /*<<< orphan*/  digest; } ;
typedef  TYPE_1__ KDF_X942 ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_LIB_PROV ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NID_undef ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int /*<<< orphan*/  PROV_R_BAD_ENCODING ; 
 int /*<<< orphan*/  PROV_R_INAVLID_UKM_LENGTH ; 
 int /*<<< orphan*/  PROV_R_MISSING_CEK_ALG ; 
 int /*<<< orphan*/  PROV_R_MISSING_MESSAGE_DIGEST ; 
 int /*<<< orphan*/  PROV_R_MISSING_SECRET ; 
 scalar_t__ X942KDF_MAX_INLEN ; 
 int /*<<< orphan*/ * ossl_prov_digest_md (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x942_encode_otherinfo (scalar_t__,size_t,int /*<<< orphan*/ *,scalar_t__,unsigned char**,size_t*,unsigned char**) ; 
 int x942kdf_hash_kdm (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,size_t,unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static int x942kdf_derive(void *vctx, unsigned char *key, size_t keylen)
{
    KDF_X942 *ctx = (KDF_X942 *)vctx;
    const EVP_MD *md = ossl_prov_digest_md(&ctx->digest);
    int ret = 0;
    unsigned char *ctr;
    unsigned char *der = NULL;
    size_t der_len = 0;

    if (ctx->secret == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_SECRET);
        return 0;
    }
    if (md == NULL) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_MESSAGE_DIGEST);
        return 0;
    }
    if (ctx->cek_nid == NID_undef) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_CEK_ALG);
        return 0;
    }
    if (ctx->ukm != NULL && ctx->ukm_len >= X942KDF_MAX_INLEN) {
        /*
         * Note the ukm length MUST be 512 bits.
         * For backwards compatibility the old check is being done.
         */
        ERR_raise(ERR_LIB_PROV, PROV_R_INAVLID_UKM_LENGTH);
        return 0;
    }
    if (keylen != ctx->dkm_len) {
        ERR_raise(ERR_LIB_PROV, PROV_R_MISSING_CEK_ALG);
        return 0;
    }
    /* generate the otherinfo der */
    if (!x942_encode_otherinfo(ctx->cek_nid, ctx->dkm_len,
                               ctx->ukm, ctx->ukm_len,
                               &der, &der_len, &ctr)) {
        ERR_raise(ERR_LIB_PROV, PROV_R_BAD_ENCODING);
        return 0;
    }
    ret = x942kdf_hash_kdm(md, ctx->secret, ctx->secret_len,
                           der, der_len, ctr, key, keylen);
    OPENSSL_free(der);
    return ret;
}