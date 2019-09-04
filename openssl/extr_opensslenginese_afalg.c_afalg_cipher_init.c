#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bfd; int /*<<< orphan*/  sfd; int /*<<< orphan*/  init_done; int /*<<< orphan*/  aio; } ;
typedef  TYPE_1__ afalg_ctx ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 scalar_t__ ALG_AES_IV_LEN ; 
 int ALG_MAX_SALG_NAME ; 
 int /*<<< orphan*/  ALG_WARN (char*,char*,int,...) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_cipher (int /*<<< orphan*/ *) ; 
 TYPE_1__* EVP_CIPHER_CTX_get_cipher_data (int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_CIPHER_CTX_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_key_length (int /*<<< orphan*/ *) ; 
 int EVP_CIPHER_CTX_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAGIC_INIT_NUM ; 
#define  NID_aes_128_cbc 130 
#define  NID_aes_192_cbc 129 
#define  NID_aes_256_cbc 128 
 int afalg_create_sk (TYPE_1__*,char*,char*) ; 
 scalar_t__ afalg_init_aio (int /*<<< orphan*/ *) ; 
 int afalg_set_key (TYPE_1__*,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static int afalg_cipher_init(EVP_CIPHER_CTX *ctx, const unsigned char *key,
                             const unsigned char *iv, int enc)
{
    int ciphertype;
    int ret;
    afalg_ctx *actx;
    char ciphername[ALG_MAX_SALG_NAME];

    if (ctx == NULL || key == NULL) {
        ALG_WARN("%s(%d): Null Parameter\n", __FILE__, __LINE__);
        return 0;
    }

    if (EVP_CIPHER_CTX_cipher(ctx) == NULL) {
        ALG_WARN("%s(%d): Cipher object NULL\n", __FILE__, __LINE__);
        return 0;
    }

    actx = EVP_CIPHER_CTX_get_cipher_data(ctx);
    if (actx == NULL) {
        ALG_WARN("%s(%d): Cipher data NULL\n", __FILE__, __LINE__);
        return 0;
    }

    ciphertype = EVP_CIPHER_CTX_nid(ctx);
    switch (ciphertype) {
    case NID_aes_128_cbc:
    case NID_aes_192_cbc:
    case NID_aes_256_cbc:
        strncpy(ciphername, "cbc(aes)", ALG_MAX_SALG_NAME);
        break;
    default:
        ALG_WARN("%s(%d): Unsupported Cipher type %d\n", __FILE__, __LINE__,
                 ciphertype);
        return 0;
    }
    ciphername[ALG_MAX_SALG_NAME-1]='\0';

    if (ALG_AES_IV_LEN != EVP_CIPHER_CTX_iv_length(ctx)) {
        ALG_WARN("%s(%d): Unsupported IV length :%d\n", __FILE__, __LINE__,
                 EVP_CIPHER_CTX_iv_length(ctx));
        return 0;
    }

    /* Setup AFALG socket for crypto processing */
    ret = afalg_create_sk(actx, "skcipher", ciphername);
    if (ret < 1)
        return 0;


    ret = afalg_set_key(actx, key, EVP_CIPHER_CTX_key_length(ctx));
    if (ret < 1)
        goto err;

    /* Setup AIO ctx to allow async AFALG crypto processing */
    if (afalg_init_aio(&actx->aio) == 0)
        goto err;

# ifdef ALG_ZERO_COPY
    pipe(actx->zc_pipe);
# endif

    actx->init_done = MAGIC_INIT_NUM;

    return 1;

err:
    close(actx->sfd);
    close(actx->bfd);
    return 0;
}