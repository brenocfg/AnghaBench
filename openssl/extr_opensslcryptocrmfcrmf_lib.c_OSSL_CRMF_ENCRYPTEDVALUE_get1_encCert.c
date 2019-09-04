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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_9__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__* encValue; TYPE_1__* symmAlg; TYPE_4__* encSymmKey; } ;
struct TYPE_7__ {size_t length; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_3__ OSSL_CRMF_ENCRYPTEDVALUE ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  TYPE_4__ ASN1_BIT_STRING ;

/* Variables and functions */
 size_t ASN1_TYPE_get_octetstring (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT ; 
 int /*<<< orphan*/  CRMF_R_ERROR_DECODING_CERTIFICATE ; 
 int /*<<< orphan*/  CRMF_R_ERROR_DECRYPTING_CERTIFICATE ; 
 int /*<<< orphan*/  CRMF_R_ERROR_DECRYPTING_SYMMETRIC_KEY ; 
 int /*<<< orphan*/  CRMF_R_MALFORMED_IV ; 
 int /*<<< orphan*/  CRMF_R_NULL_ARGUMENT ; 
 int /*<<< orphan*/  CRMF_R_UNSUPPORTED_CIPHER ; 
 int /*<<< orphan*/  CRMFerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_set_padding (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t EVP_CIPHER_block_size (int /*<<< orphan*/  const*) ; 
 size_t EVP_CIPHER_iv_length (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_DecryptFinal (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_DecryptInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  EVP_DecryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_decrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EVP_PKEY_decrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_cipherbynid (int) ; 
 int OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/ * d2i_X509 (int /*<<< orphan*/ *,unsigned char const**,int) ; 

X509 *OSSL_CRMF_ENCRYPTEDVALUE_get1_encCert(OSSL_CRMF_ENCRYPTEDVALUE *ecert,
                                            EVP_PKEY *pkey)
{
    X509 *cert = NULL; /* decrypted certificate */
    EVP_CIPHER_CTX *evp_ctx = NULL; /* context for symmetric encryption */
    unsigned char *ek = NULL; /* decrypted symmetric encryption key */
    const EVP_CIPHER *cipher = NULL; /* used cipher */
    unsigned char *iv = NULL; /* initial vector for symmetric encryption */
    unsigned char *outbuf = NULL; /* decryption output buffer */
    const unsigned char *p = NULL; /* needed for decoding ASN1 */
    int symmAlg = 0; /* NIDs for symmetric algorithm */
    int n, outlen = 0;
    EVP_PKEY_CTX *pkctx = NULL; /* private key context */

    if (ecert == NULL || ecert->symmAlg == NULL || ecert->encSymmKey == NULL
            || ecert->encValue == NULL || pkey == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_NULL_ARGUMENT);
        return NULL;
    }
    if ((symmAlg = OBJ_obj2nid(ecert->symmAlg->algorithm)) == 0) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_UNSUPPORTED_CIPHER);
        return NULL;
    }

    /* first the symmetric key needs to be decrypted */
    pkctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (pkctx != NULL && EVP_PKEY_decrypt_init(pkctx)) {
        ASN1_BIT_STRING *encKey = ecert->encSymmKey;
        size_t eksize = 0;

        if (EVP_PKEY_decrypt(pkctx, NULL, &eksize, encKey->data, encKey->length)
                <= 0
                || (ek = OPENSSL_malloc(eksize)) == NULL
                || EVP_PKEY_decrypt(pkctx, ek, &eksize, encKey->data,
                                    encKey->length) <= 0) {
            CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                    CRMF_R_ERROR_DECRYPTING_SYMMETRIC_KEY);
            goto end;
        }
    } else {
        goto oom;
    }

    /* select symmetric cipher based on algorithm given in message */
    if ((cipher = EVP_get_cipherbynid(symmAlg)) == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_UNSUPPORTED_CIPHER);
        goto end;
    }
    if ((iv = OPENSSL_malloc(EVP_CIPHER_iv_length(cipher))) == NULL)
        goto oom;
    if (ASN1_TYPE_get_octetstring(ecert->symmAlg->parameter, iv,
                                   EVP_CIPHER_iv_length(cipher))
        != EVP_CIPHER_iv_length(cipher)) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_MALFORMED_IV);
        goto end;
    }

    /*
     * d2i_X509 changes the given pointer, so use p for decoding the message and
     * keep the original pointer in outbuf so the memory can be freed later
     */
    if ((p = outbuf = OPENSSL_malloc(ecert->encValue->length +
                                     EVP_CIPHER_block_size(cipher))) == NULL
            || (evp_ctx = EVP_CIPHER_CTX_new()) == NULL)
        goto oom;
    EVP_CIPHER_CTX_set_padding(evp_ctx, 0);

    if (!EVP_DecryptInit(evp_ctx, cipher, ek, iv)
            || !EVP_DecryptUpdate(evp_ctx, outbuf, &outlen,
                                  ecert->encValue->data,
                                  ecert->encValue->length)
            || !EVP_DecryptFinal(evp_ctx, outbuf + outlen, &n)) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_ERROR_DECRYPTING_CERTIFICATE);
        goto end;
    }
    outlen += n;

    /* convert decrypted certificate from DER to internal ASN.1 structure */
    if ((cert = d2i_X509(NULL, &p, outlen)) == NULL) {
        CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT,
                CRMF_R_ERROR_DECODING_CERTIFICATE);
    }
    goto end;

 oom:
    CRMFerr(CRMF_F_OSSL_CRMF_ENCRYPTEDVALUE_GET1_ENCCERT, ERR_R_MALLOC_FAILURE);
 end:
    EVP_PKEY_CTX_free(pkctx);
    OPENSSL_free(outbuf);
    EVP_CIPHER_CTX_free(evp_ctx);
    OPENSSL_free(ek);
    OPENSSL_free(iv);
    return cert;
}