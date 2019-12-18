#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {TYPE_3__* mac; int /*<<< orphan*/  iterationCount; TYPE_2__* salt; TYPE_1__* owf; } ;
struct TYPE_8__ {int /*<<< orphan*/ * algorithm; } ;
struct TYPE_7__ {unsigned char* data; unsigned int length; } ;
struct TYPE_6__ {int /*<<< orphan*/  algorithm; } ;
typedef  int /*<<< orphan*/  OSSL_PARAM ;
typedef  TYPE_4__ OSSL_CRMF_PBMPARAMETER ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  EVP_MAC_CTX ;
typedef  int /*<<< orphan*/  EVP_MAC ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_INTEGER_get_int64 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_PBM_NEW ; 
 int /*<<< orphan*/  CRMF_R_BAD_PBM_ITERATIONCOUNT ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_ALGORITHM ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,unsigned int*) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_CTX_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_CTX_set_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MAC_fetch (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_final (int /*<<< orphan*/ *,unsigned char*,size_t*,int) ; 
 int /*<<< orphan*/  EVP_MAC_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MAC_update (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PBE_TYPE_PRF ; 
 int /*<<< orphan*/  EVP_PBE_find (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int NID_undef ; 
 char* OBJ_nid2sn (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ *) ; 
 scalar_t__ OBJ_obj2txt (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 
 int OSSL_CRMF_PBM_MAX_ITERATION_COUNT ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_DIGEST ; 
 int /*<<< orphan*/  OSSL_MAC_PARAM_KEY ; 
 int /*<<< orphan*/  OSSL_PARAM_END ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_octet_string (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  OSSL_PARAM_construct_utf8_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int OSSL_CRMF_pbm_new(const OSSL_CRMF_PBMPARAMETER *pbmp,
                      const unsigned char *msg, size_t msglen,
                      const unsigned char *sec, size_t seclen,
                      unsigned char **out, size_t *outlen)
{
    int mac_nid, hmac_md_nid = NID_undef;
    const char *mdname = NULL;
    const EVP_MD *m = NULL;
    EVP_MD_CTX *ctx = NULL;
    unsigned char basekey[EVP_MAX_MD_SIZE];
    unsigned int bklen = EVP_MAX_MD_SIZE;
    int64_t iterations;
    unsigned char *mac_res = 0;
    int ok = 0;
    EVP_MAC *mac = NULL;
    EVP_MAC_CTX *mctx = NULL;
    OSSL_PARAM macparams[3] =
        { OSSL_PARAM_END, OSSL_PARAM_END, OSSL_PARAM_END };

    if (out == NULL || pbmp == NULL || pbmp->mac == NULL
            || pbmp->mac->algorithm == NULL || msg == NULL || sec == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBM_NEW, CRMF_R_NULL_ARGUMENT);
        goto err;
    }
    if ((mac_res = OPENSSL_malloc(EVP_MAX_MD_SIZE)) == NULL)
        goto err;

    /*
     * owf identifies the hash algorithm and associated parameters used to
     * compute the key used in the MAC process.  All implementations MUST
     * support SHA-1.
     */
    if ((m = EVP_get_digestbyobj(pbmp->owf->algorithm)) == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBM_NEW, CRMF_R_UNSUPPORTED_ALGORITHM);
        goto err;
    }

    if ((ctx = EVP_MD_CTX_new()) == NULL)
        goto err;

    /* compute the basekey of the salted secret */
    if (!EVP_DigestInit_ex(ctx, m, NULL))
        goto err;
    /* first the secret */
    if (!EVP_DigestUpdate(ctx, sec, seclen))
        goto err;
    /* then the salt */
    if (!EVP_DigestUpdate(ctx, pbmp->salt->data, pbmp->salt->length))
        goto err;
    if (!EVP_DigestFinal_ex(ctx, basekey, &bklen))
        goto err;
    if (!ASN1_INTEGER_get_int64(&iterations, pbmp->iterationCount)
            || iterations < 100 /* min from RFC */
            || iterations > OSSL_CRMF_PBM_MAX_ITERATION_COUNT) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBM_NEW, CRMF_R_BAD_PBM_ITERATIONCOUNT);
        goto err;
    }

    /* the first iteration was already done above */
    while (--iterations > 0) {
        if (!EVP_DigestInit_ex(ctx, m, NULL))
            goto err;
        if (!EVP_DigestUpdate(ctx, basekey, bklen))
            goto err;
        if (!EVP_DigestFinal_ex(ctx, basekey, &bklen))
            goto err;
    }

    /*
     * mac identifies the algorithm and associated parameters of the MAC
     * function to be used.  All implementations MUST support HMAC-SHA1 [HMAC].
     * All implementations SHOULD support DES-MAC and Triple-DES-MAC [PKCS11].
     */
    mac_nid = OBJ_obj2nid(pbmp->mac->algorithm);

    if (!EVP_PBE_find(EVP_PBE_TYPE_PRF, mac_nid, NULL, &hmac_md_nid, NULL)
        || ((mdname = OBJ_nid2sn(hmac_md_nid)) == NULL)) {
        CRMFerr(CRMF_F_OSSL_CRMF_PBM_NEW, CRMF_R_UNSUPPORTED_ALGORITHM);
        goto err;
    }

    macparams[0] =
        OSSL_PARAM_construct_utf8_string(OSSL_MAC_PARAM_DIGEST,
                                         (char *)mdname, 0);
    macparams[1] =
        OSSL_PARAM_construct_octet_string(OSSL_MAC_PARAM_KEY, basekey, bklen);
    if ((mac = EVP_MAC_fetch(NULL, "HMAC", NULL)) == NULL
            || (mctx = EVP_MAC_CTX_new(mac)) == NULL
            || !EVP_MAC_CTX_set_params(mctx, macparams)
            || !EVP_MAC_init(mctx)
            || !EVP_MAC_update(mctx, msg, msglen)
            || !EVP_MAC_final(mctx, mac_res, outlen, EVP_MAX_MD_SIZE))
        goto err;

    ok = 1;

 err:
    /* cleanup */
    OPENSSL_cleanse(basekey, bklen);
    EVP_MAC_CTX_free(mctx);
    EVP_MAC_free(mac);
    EVP_MD_CTX_free(ctx);

    if (ok == 1) {
        *out = mac_res;
        return 1;
    }

    OPENSSL_free(mac_res);

    if (pbmp != NULL && pbmp->mac != NULL) {
        char buf[128];

        if (OBJ_obj2txt(buf, sizeof(buf), pbmp->mac->algorithm, 0))
            ERR_add_error_data(1, buf);
    }
    return 0;
}