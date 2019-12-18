#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; } ;
struct TYPE_4__ {TYPE_3__* signature; int /*<<< orphan*/  algorithmIdentifier; } ;
typedef  TYPE_1__ OSSL_CRMF_POPOSIGNINGKEY ;
typedef  int /*<<< orphan*/  OSSL_CRMF_CERTREQUEST ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_BIT_STRING_set (TYPE_3__*,unsigned char*,size_t) ; 
 int ASN1_STRING_FLAG_BITS_LEFT ; 
 int /*<<< orphan*/  CRMF_F_CRMF_POPOSIGNINGKEY_INIT ; 
 int /*<<< orphan*/  CRMF_R_ERROR ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_ALG_FOR_POPSIGNINGKEY ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbynid (int) ; 
 int /*<<< orphan*/  OBJ_find_sigid_algs (int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_find_sigid_by_algs (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  V_ASN1_NULL ; 
 int /*<<< orphan*/  X509_ALGOR_set0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int i2d_OSSL_CRMF_CERTREQUEST (int /*<<< orphan*/ *,unsigned char**) ; 

__attribute__((used)) static int CRMF_poposigningkey_init(OSSL_CRMF_POPOSIGNINGKEY *ps,
                                    OSSL_CRMF_CERTREQUEST *cr,
                                    EVP_PKEY *pkey, int dgst)
{
    int len;
    size_t crlen;
    size_t siglen;
    unsigned char *crder = NULL, *sig = NULL;
    int alg_nid = 0;
    int md_nid = 0;
    const EVP_MD *alg = NULL;
    EVP_MD_CTX *ctx = NULL;
    int ret = 0;

    if (ps == NULL || cr == NULL || pkey == NULL) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT, CRMF_R_NULL_ARGUMENT);
        return 0;
    }

    /* OpenSSL defaults all bit strings to be encoded as ASN.1 NamedBitList */
    ps->signature->flags &= ~(ASN1_STRING_FLAG_BITS_LEFT | 0x07);
    ps->signature->flags |= ASN1_STRING_FLAG_BITS_LEFT;

    len = i2d_OSSL_CRMF_CERTREQUEST(cr, &crder);
    if (len < 0 || crder == NULL) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT, CRMF_R_ERROR);
        goto err;
    }
    crlen = (size_t)len;

    if (!OBJ_find_sigid_by_algs(&alg_nid, dgst, EVP_PKEY_id(pkey))) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT,
                CRMF_R_UNSUPPORTED_ALG_FOR_POPSIGNINGKEY);
        goto err;
    }
    if (!OBJ_find_sigid_algs(alg_nid, &md_nid, NULL)
            || (alg = EVP_get_digestbynid(md_nid)) == NULL) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT,
                CRMF_R_UNSUPPORTED_ALG_FOR_POPSIGNINGKEY);
        goto err;
    }
    if (!X509_ALGOR_set0(ps->algorithmIdentifier, OBJ_nid2obj(alg_nid),
                         V_ASN1_NULL, NULL)
            || (ctx = EVP_MD_CTX_new()) == NULL
            || EVP_DigestSignInit(ctx, NULL, alg, NULL, pkey) <= 0
            || EVP_DigestSignUpdate(ctx, crder, crlen) <= 0
            || EVP_DigestSignFinal(ctx, NULL, &siglen) <= 0) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT, CRMF_R_ERROR);
        goto err;
    }
    if ((sig = OPENSSL_malloc(siglen)) == NULL)
        goto err;
    if (EVP_DigestSignFinal(ctx, sig, &siglen) <= 0
            || !ASN1_BIT_STRING_set(ps->signature, sig, siglen)) {
        CRMFerr(CRMF_F_CRMF_POPOSIGNINGKEY_INIT, CRMF_R_ERROR);
        goto err;
    }
    ret = 1;

 err:
    OPENSSL_free(crder);
    EVP_MD_CTX_free(ctx);
    OPENSSL_free(sig);
    return ret;
}