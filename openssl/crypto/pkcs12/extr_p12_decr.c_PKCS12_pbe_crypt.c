#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parameter; int /*<<< orphan*/  algorithm; } ;
typedef  TYPE_1__ X509_ALGOR ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_EVP_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ EVP_CIPHER_CTX_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int /*<<< orphan*/  EVP_CipherFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int /*<<< orphan*/  EVP_CipherUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char const*,int) ; 
 int /*<<< orphan*/  EVP_PBE_CipherInit (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (scalar_t__) ; 
 int /*<<< orphan*/  PKCS12_F_PKCS12_PBE_CRYPT ; 
 int /*<<< orphan*/  PKCS12_R_PKCS12_ALGOR_CIPHERINIT_ERROR ; 
 int /*<<< orphan*/  PKCS12_R_PKCS12_CIPHERFINAL_ERROR ; 
 int /*<<< orphan*/  PKCS12err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned char *PKCS12_pbe_crypt(const X509_ALGOR *algor,
                                const char *pass, int passlen,
                                const unsigned char *in, int inlen,
                                unsigned char **data, int *datalen, int en_de)
{
    unsigned char *out = NULL;
    int outlen, i;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (ctx == NULL) {
        PKCS12err(PKCS12_F_PKCS12_PBE_CRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    /* Decrypt data */
    if (!EVP_PBE_CipherInit(algor->algorithm, pass, passlen,
                            algor->parameter, ctx, en_de)) {
        PKCS12err(PKCS12_F_PKCS12_PBE_CRYPT,
                  PKCS12_R_PKCS12_ALGOR_CIPHERINIT_ERROR);
        goto err;
    }

    if ((out = OPENSSL_malloc(inlen + EVP_CIPHER_CTX_block_size(ctx)))
            == NULL) {
        PKCS12err(PKCS12_F_PKCS12_PBE_CRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (!EVP_CipherUpdate(ctx, out, &i, in, inlen)) {
        OPENSSL_free(out);
        out = NULL;
        PKCS12err(PKCS12_F_PKCS12_PBE_CRYPT, ERR_R_EVP_LIB);
        goto err;
    }

    outlen = i;
    if (!EVP_CipherFinal_ex(ctx, out + i, &i)) {
        OPENSSL_free(out);
        out = NULL;
        PKCS12err(PKCS12_F_PKCS12_PBE_CRYPT,
                  PKCS12_R_PKCS12_CIPHERFINAL_ERROR);
        goto err;
    }
    outlen += i;
    if (datalen)
        *datalen = outlen;
    if (data)
        *data = out;
 err:
    EVP_CIPHER_CTX_free(ctx);
    return out;

}