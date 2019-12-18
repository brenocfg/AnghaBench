#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  enc_digest; scalar_t__ auth_attr; int /*<<< orphan*/  pkey; TYPE_1__* digest_alg; } ;
struct TYPE_5__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_2__ PKCS7_SIGNER_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_ITEM_rptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int ASN1_item_i2d (int /*<<< orphan*/ *,unsigned char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 scalar_t__ EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_PKCS7_SIGN ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_SIGN ; 
 int /*<<< orphan*/ * EVP_get_digestbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  PKCS7_ATTR_SIGN ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_SIGNER_INFO_SIGN ; 
 int /*<<< orphan*/  PKCS7_R_CTRL_ERROR ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int PKCS7_SIGNER_INFO_sign(PKCS7_SIGNER_INFO *si)
{
    EVP_MD_CTX *mctx;
    EVP_PKEY_CTX *pctx = NULL;
    unsigned char *abuf = NULL;
    int alen;
    size_t siglen;
    const EVP_MD *md = NULL;

    md = EVP_get_digestbyobj(si->digest_alg->algorithm);
    if (md == NULL)
        return 0;

    mctx = EVP_MD_CTX_new();
    if (mctx == NULL) {
        PKCS7err(PKCS7_F_PKCS7_SIGNER_INFO_SIGN, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_DigestSignInit(mctx, &pctx, md, NULL, si->pkey) <= 0)
        goto err;

    /*
     * TODO(3.0): This causes problems when providers are in use, so disabled
     * for now. Can we get rid of this completely? AFAICT this ctrl has never
     * been used since it was first put in. All internal implementations just
     * return 1 and ignore this ctrl and have always done so by the looks of
     * things. To fix this we could convert this ctrl into a param, which would
     * require us to send all the signer info data as a set of params...but that
     * is non-trivial and since this isn't used by anything it may be better
     * just to remove it. The original commit that added it had this
     * justification in CHANGES:
     *
     * "During PKCS7 signing pass the PKCS7 SignerInfo structure to the
     *  EVP_PKEY_METHOD before and after signing via the
     *  EVP_PKEY_CTRL_PKCS7_SIGN ctrl. It can then customise the structure
     *  before and/or after signing if necessary."
     */
#if 0
    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_SIGN,
                          EVP_PKEY_CTRL_PKCS7_SIGN, 0, si) <= 0) {
        PKCS7err(PKCS7_F_PKCS7_SIGNER_INFO_SIGN, PKCS7_R_CTRL_ERROR);
        goto err;
    }
#endif

    alen = ASN1_item_i2d((ASN1_VALUE *)si->auth_attr, &abuf,
                         ASN1_ITEM_rptr(PKCS7_ATTR_SIGN));
    if (!abuf)
        goto err;
    if (EVP_DigestSignUpdate(mctx, abuf, alen) <= 0)
        goto err;
    OPENSSL_free(abuf);
    abuf = NULL;
    if (EVP_DigestSignFinal(mctx, NULL, &siglen) <= 0)
        goto err;
    abuf = OPENSSL_malloc(siglen);
    if (abuf == NULL)
        goto err;
    if (EVP_DigestSignFinal(mctx, abuf, &siglen) <= 0)
        goto err;

    /*
     * TODO(3.0): This causes problems when providers are in use, so disabled
     * for now. Can we get rid of this completely? AFAICT this ctrl has never
     * been used since it was first put in. All internal implementations just
     * return 1 and ignore this ctrl and have always done so by the looks of
     * things. To fix this we could convert this ctrl into a param, which would
     * require us to send all the signer info data as a set of params...but that
     * is non-trivial and since this isn't used by anything it may be better
     * just to remove it. The original commit that added it had this
     * justification in CHANGES:
     *
     * "During PKCS7 signing pass the PKCS7 SignerInfo structure to the
     *  EVP_PKEY_METHOD before and after signing via the
     *  EVP_PKEY_CTRL_PKCS7_SIGN ctrl. It can then customise the structure
     *  before and/or after signing if necessary."
     */
#if 0
    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_SIGN,
                          EVP_PKEY_CTRL_PKCS7_SIGN, 1, si) <= 0) {
        PKCS7err(PKCS7_F_PKCS7_SIGNER_INFO_SIGN, PKCS7_R_CTRL_ERROR);
        goto err;
    }
#endif

    EVP_MD_CTX_free(mctx);

    ASN1_STRING_set0(si->enc_digest, abuf, siglen);

    return 1;

 err:
    OPENSSL_free(abuf);
    EVP_MD_CTX_free(mctx);
    return 0;

}