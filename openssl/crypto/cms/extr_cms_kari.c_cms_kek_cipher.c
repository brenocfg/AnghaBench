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
struct TYPE_3__ {int /*<<< orphan*/ * pctx; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ CMS_KeyAgreeRecipientInfo ;

/* Variables and functions */
 size_t EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVP_CipherInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_CipherUpdate (int /*<<< orphan*/ ,unsigned char*,int*,unsigned char const*,size_t) ; 
 int EVP_MAX_KEY_LENGTH ; 
 int /*<<< orphan*/  EVP_PKEY_CTX_free (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_derive (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,size_t) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (int) ; 

__attribute__((used)) static int cms_kek_cipher(unsigned char **pout, size_t *poutlen,
                          const unsigned char *in, size_t inlen,
                          CMS_KeyAgreeRecipientInfo *kari, int enc)
{
    /* Key encryption key */
    unsigned char kek[EVP_MAX_KEY_LENGTH];
    size_t keklen;
    int rv = 0;
    unsigned char *out = NULL;
    int outlen;
    keklen = EVP_CIPHER_CTX_key_length(kari->ctx);
    if (keklen > EVP_MAX_KEY_LENGTH)
        return 0;
    /* Derive KEK */
    if (EVP_PKEY_derive(kari->pctx, kek, &keklen) <= 0)
        goto err;
    /* Set KEK in context */
    if (!EVP_CipherInit_ex(kari->ctx, NULL, NULL, kek, NULL, enc))
        goto err;
    /* obtain output length of ciphered key */
    if (!EVP_CipherUpdate(kari->ctx, NULL, &outlen, in, inlen))
        goto err;
    out = OPENSSL_malloc(outlen);
    if (out == NULL)
        goto err;
    if (!EVP_CipherUpdate(kari->ctx, out, &outlen, in, inlen))
        goto err;
    *pout = out;
    *poutlen = (size_t)outlen;
    rv = 1;

 err:
    OPENSSL_cleanse(kek, keklen);
    if (!rv)
        OPENSSL_free(out);
    EVP_CIPHER_CTX_reset(kari->ctx);
    /* FIXME: WHY IS kari->pctx freed here?  /RL */
    EVP_PKEY_CTX_free(kari->pctx);
    kari->pctx = NULL;
    return rv;
}