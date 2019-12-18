#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  enc_key; int /*<<< orphan*/  cert; } ;
typedef  TYPE_1__ PKCS7_RECIP_INFO ;
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_STRING_set0 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  EVP_PKEY_CTRL_PKCS7_ENCRYPT ; 
 scalar_t__ EVP_PKEY_CTX_ctrl (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_PKEY_CTX_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_OP_ENCRYPT ; 
 scalar_t__ EVP_PKEY_encrypt (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,int) ; 
 scalar_t__ EVP_PKEY_encrypt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (size_t) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_ENCODE_RINFO ; 
 int /*<<< orphan*/  PKCS7_R_CTRL_ERROR ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * X509_get0_pubkey (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pkcs7_encode_rinfo(PKCS7_RECIP_INFO *ri,
                              unsigned char *key, int keylen)
{
    EVP_PKEY_CTX *pctx = NULL;
    EVP_PKEY *pkey = NULL;
    unsigned char *ek = NULL;
    int ret = 0;
    size_t eklen;

    pkey = X509_get0_pubkey(ri->cert);
    if (pkey == NULL)
        return 0;

    pctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (pctx == NULL)
        return 0;

    if (EVP_PKEY_encrypt_init(pctx) <= 0)
        goto err;

    if (EVP_PKEY_CTX_ctrl(pctx, -1, EVP_PKEY_OP_ENCRYPT,
                          EVP_PKEY_CTRL_PKCS7_ENCRYPT, 0, ri) <= 0) {
        PKCS7err(PKCS7_F_PKCS7_ENCODE_RINFO, PKCS7_R_CTRL_ERROR);
        goto err;
    }

    if (EVP_PKEY_encrypt(pctx, NULL, &eklen, key, keylen) <= 0)
        goto err;

    ek = OPENSSL_malloc(eklen);

    if (ek == NULL) {
        PKCS7err(PKCS7_F_PKCS7_ENCODE_RINFO, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (EVP_PKEY_encrypt(pctx, ek, &eklen, key, keylen) <= 0)
        goto err;

    ASN1_STRING_set0(ri->enc_key, ek, eklen);
    ek = NULL;

    ret = 1;

 err:
    EVP_PKEY_CTX_free(pctx);
    OPENSSL_free(ek);
    return ret;

}