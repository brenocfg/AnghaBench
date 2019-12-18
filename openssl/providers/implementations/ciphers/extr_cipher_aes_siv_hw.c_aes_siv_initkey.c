#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* ctr; void* cbc; int /*<<< orphan*/  siv; } ;
typedef  int /*<<< orphan*/  SIV128_CONTEXT ;
typedef  TYPE_1__ PROV_AES_SIV_CTX ;

/* Variables and functions */
 int CRYPTO_siv128_init (int /*<<< orphan*/ *,unsigned char const*,size_t,void*,void*) ; 
 void* EVP_CIPHER_fetch (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int aes_siv_initkey(void *vctx, const unsigned char *key, size_t keylen)
{
    PROV_AES_SIV_CTX *ctx = (PROV_AES_SIV_CTX *)vctx;
    SIV128_CONTEXT *sctx = &ctx->siv;
    size_t klen  = keylen / 2;

    switch (klen) {
    case 16:
        ctx->cbc = EVP_CIPHER_fetch(NULL, "AES-128-CBC", "");
        ctx->ctr = EVP_CIPHER_fetch(NULL, "AES-128-CTR", "");
        break;
    case 24:
        ctx->cbc = EVP_CIPHER_fetch(NULL, "AES-192-CBC", "");
        ctx->ctr = EVP_CIPHER_fetch(NULL, "AES-192-CTR", "");
        break;
    case 32:
        ctx->cbc = EVP_CIPHER_fetch(NULL, "AES-256-CBC", "");
        ctx->ctr = EVP_CIPHER_fetch(NULL, "AES-256-CTR", "");
        break;
    default:
        return 0;
    }
    /*
     * klen is the length of the underlying cipher, not the input key,
     * which should be twice as long
     */
    return CRYPTO_siv128_init(sctx, key, klen, ctx->cbc, ctx->ctr);
}