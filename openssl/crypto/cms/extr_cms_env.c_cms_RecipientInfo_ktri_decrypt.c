#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_5__ X509_ALGOR ;
struct TYPE_16__ {TYPE_2__* envelopedData; } ;
struct TYPE_22__ {TYPE_3__ d; } ;
struct TYPE_21__ {unsigned char* key; size_t keylen; TYPE_5__* contentEncryptionAlgorithm; int /*<<< orphan*/  debug; scalar_t__ havenocert; } ;
struct TYPE_20__ {int /*<<< orphan*/ * pctx; TYPE_4__* encryptedKey; int /*<<< orphan*/ * pkey; } ;
struct TYPE_14__ {TYPE_7__* ktri; } ;
struct TYPE_19__ {TYPE_1__ d; } ;
struct TYPE_17__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_8__* encryptedContentInfo; } ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_6__ CMS_RecipientInfo ;
typedef  TYPE_7__ CMS_KeyTransRecipientInfo ;
typedef  TYPE_8__ CMS_EncryptedContentInfo ;
typedef  TYPE_9__ CMS_ContentInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT ; 
 int /*<<< orphan*/  CMS_R_CMS_LIB ; 
 int /*<<< orphan*/  CMS_R_CTRL_ERROR ; 
 int /*<<< orphan*/  CMS_R_NO_PRIVATE_KEY ; 
 int /*<<< orphan*/  CMS_R_UNKNOWN_CIPHER ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 size_t EVP_CIPHER_key_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_CMS_DECRYPT ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_DECRYPT ; 
 scalar_t__ EVP_PKEY_decrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_decrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_cipherbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  cms_env_asn1_ctrl (TYPE_6__*,int) ; 

__attribute__((used)) static int cms_RecipientInfo_ktri_decrypt(CMS_ContentInfo *cms,
                                          CMS_RecipientInfo *ri)
{
    CMS_KeyTransRecipientInfo *ktri = ri->d.ktri;
    EVP_PKEY *pkey = ktri->pkey;
    unsigned char *ek = NULL;
    size_t eklen;
    int ret = 0;
    size_t fixlen = 0;
    CMS_EncryptedContentInfo *ec;
    ec = cms->d.envelopedData->encryptedContentInfo;

    if (ktri->pkey == NULL) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT, CMS_R_NO_PRIVATE_KEY);
        return 0;
    }

    if (cms->d.envelopedData->encryptedContentInfo->havenocert
            && !cms->d.envelopedData->encryptedContentInfo->debug) {
        X509_ALGOR *calg = ec->contentEncryptionAlgorithm;
        const EVP_CIPHER *ciph = EVP_get_cipherbyobj(calg->algorithm);

        if (ciph == NULL) {
            CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT, CMS_R_UNKNOWN_CIPHER);
            return 0;
        }

        fixlen = EVP_CIPHER_key_length(ciph);
    }

    ktri->pctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (ktri->pctx == NULL)
        return 0;

    if (EVP_PKEY_decrypt_init(ktri->pctx) <= 0)
        goto err;

    if (!cms_env_asn1_ctrl(ri, 1))
        goto err;

    if (EVP_PKEY_CTX_ctrl(ktri->pctx, -1, EVP_PKEY_OP_DECRYPT,
                          EVP_PKEY_CTRL_CMS_DECRYPT, 0, ri) <= 0) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT, CMS_R_CTRL_ERROR);
        goto err;
    }

    if (EVP_PKEY_decrypt(ktri->pctx, NULL, &eklen,
                         ktri->encryptedKey->data,
                         ktri->encryptedKey->length) <= 0)
        goto err;

    ek = OPENSSL_malloc(eklen);

    if (ek == NULL) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_PKEY_decrypt(ktri->pctx, ek, &eklen,
                         ktri->encryptedKey->data,
                         ktri->encryptedKey->length) <= 0
            || eklen == 0
            || (fixlen != 0 && eklen != fixlen)) {
        CMSerr(CMS_F_CMS_RECIPIENTINFO_KTRI_DECRYPT, CMS_R_CMS_LIB);
        goto err;
    }

    ret = 1;

    OPENSSL_clear_free(ec->key, ec->keylen);
    ec->key = ek;
    ec->keylen = eklen;

 err:
    EVP_PKEY_CTX_free(ktri->pctx);
    ktri->pctx = NULL;
    if (!ret)
        OPENSSL_free(ek);

    return ret;
}