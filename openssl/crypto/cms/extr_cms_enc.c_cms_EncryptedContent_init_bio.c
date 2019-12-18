#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_9__ {unsigned char* key; size_t keylen; scalar_t__ debug; int /*<<< orphan*/ * cipher; TYPE_1__* contentEncryptionAlgorithm; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_2__ CMS_EncryptedContentInfo ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_TYPE_free (TYPE_4__*) ; 
 TYPE_4__* ASN1_TYPE_new () ; 
 int /*<<< orphan*/  BIO_f_cipher () ; 
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_cipher_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO ; 
 int /*<<< orphan*/  CMS_R_CIPHER_INITIALISATION_ERROR ; 
 int /*<<< orphan*/  CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR ; 
 int /*<<< orphan*/  CMS_R_INVALID_KEY_LENGTH ; 
 int /*<<< orphan*/  CMS_R_UNKNOWN_CIPHER ; 
 int /*<<< orphan*/  CMSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 int EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 size_t EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_rand_key (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ EVP_CIPHER_CTX_set_key_length (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_type (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_asn1_to_param (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ EVP_CIPHER_param_to_asn1 (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ EVP_CipherInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,unsigned char*,unsigned char*,int) ; 
 int EVP_MAX_IV_LENGTH ; 
 int /*<<< orphan*/ * EVP_get_cipherbyobj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (unsigned char*,size_t) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 scalar_t__ RAND_bytes (unsigned char*,int) ; 
 scalar_t__ V_ASN1_UNDEF ; 

BIO *cms_EncryptedContent_init_bio(CMS_EncryptedContentInfo *ec)
{
    BIO *b;
    EVP_CIPHER_CTX *ctx;
    const EVP_CIPHER *ciph;
    X509_ALGOR *calg = ec->contentEncryptionAlgorithm;
    unsigned char iv[EVP_MAX_IV_LENGTH], *piv = NULL;
    unsigned char *tkey = NULL;
    size_t tkeylen = 0;

    int ok = 0;

    int enc, keep_key = 0;

    enc = ec->cipher ? 1 : 0;

    b = BIO_new(BIO_f_cipher());
    if (b == NULL) {
        CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    BIO_get_cipher_ctx(b, &ctx);

    if (enc) {
        ciph = ec->cipher;
        /*
         * If not keeping key set cipher to NULL so subsequent calls decrypt.
         */
        if (ec->key)
            ec->cipher = NULL;
    } else {
        ciph = EVP_get_cipherbyobj(calg->algorithm);

        if (!ciph) {
            CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO, CMS_R_UNKNOWN_CIPHER);
            goto err;
        }
    }

    if (EVP_CipherInit_ex(ctx, ciph, NULL, NULL, NULL, enc) <= 0) {
        CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
               CMS_R_CIPHER_INITIALISATION_ERROR);
        goto err;
    }

    if (enc) {
        int ivlen;
        calg->algorithm = OBJ_nid2obj(EVP_CIPHER_CTX_type(ctx));
        /* Generate a random IV if we need one */
        ivlen = EVP_CIPHER_CTX_iv_length(ctx);
        if (ivlen > 0) {
            if (RAND_bytes(iv, ivlen) <= 0)
                goto err;
            piv = iv;
        }
    } else if (EVP_CIPHER_asn1_to_param(ctx, calg->parameter) <= 0) {
        CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
               CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR);
        goto err;
    }
    tkeylen = EVP_CIPHER_CTX_key_length(ctx);
    /* Generate random session key */
    if (!enc || !ec->key) {
        tkey = OPENSSL_malloc(tkeylen);
        if (tkey == NULL) {
            CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (EVP_CIPHER_CTX_rand_key(ctx, tkey) <= 0)
            goto err;
    }

    if (!ec->key) {
        ec->key = tkey;
        ec->keylen = tkeylen;
        tkey = NULL;
        if (enc)
            keep_key = 1;
        else
            ERR_clear_error();

    }

    if (ec->keylen != tkeylen) {
        /* If necessary set key length */
        if (EVP_CIPHER_CTX_set_key_length(ctx, ec->keylen) <= 0) {
            /*
             * Only reveal failure if debugging so we don't leak information
             * which may be useful in MMA.
             */
            if (enc || ec->debug) {
                CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
                       CMS_R_INVALID_KEY_LENGTH);
                goto err;
            } else {
                /* Use random key */
                OPENSSL_clear_free(ec->key, ec->keylen);
                ec->key = tkey;
                ec->keylen = tkeylen;
                tkey = NULL;
                ERR_clear_error();
            }
        }
    }

    if (EVP_CipherInit_ex(ctx, NULL, NULL, ec->key, piv, enc) <= 0) {
        CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
               CMS_R_CIPHER_INITIALISATION_ERROR);
        goto err;
    }
    if (enc) {
        calg->parameter = ASN1_TYPE_new();
        if (calg->parameter == NULL) {
            CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO, ERR_R_MALLOC_FAILURE);
            goto err;
        }
        if (EVP_CIPHER_param_to_asn1(ctx, calg->parameter) <= 0) {
            CMSerr(CMS_F_CMS_ENCRYPTEDCONTENT_INIT_BIO,
                   CMS_R_CIPHER_PARAMETER_INITIALISATION_ERROR);
            goto err;
        }
        /* If parameter type not set omit parameter */
        if (calg->parameter->type == V_ASN1_UNDEF) {
            ASN1_TYPE_free(calg->parameter);
            calg->parameter = NULL;
        }
    }
    ok = 1;

 err:
    if (!keep_key || !ok) {
        OPENSSL_clear_free(ec->key, ec->keylen);
        ec->key = NULL;
    }
    OPENSSL_clear_free(tkey, tkeylen);
    if (ok)
        return b;
    BIO_free(b);
    return NULL;
}