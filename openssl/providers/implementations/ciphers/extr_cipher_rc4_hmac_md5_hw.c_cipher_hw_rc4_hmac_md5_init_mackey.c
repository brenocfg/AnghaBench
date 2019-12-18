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
typedef  int /*<<< orphan*/  hmac_key ;
struct TYPE_2__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ PROV_RC4_HMAC_MD5_CTX ;
typedef  int /*<<< orphan*/  PROV_CIPHER_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cipher_hw_rc4_hmac_md5_init_mackey(PROV_CIPHER_CTX *bctx,
                                               const unsigned char *key,
                                               size_t len)
{
    PROV_RC4_HMAC_MD5_CTX *ctx = (PROV_RC4_HMAC_MD5_CTX *)bctx;
    unsigned int i;
    unsigned char hmac_key[64];

    memset(hmac_key, 0, sizeof(hmac_key));

    if (len > (int)sizeof(hmac_key)) {
        MD5_Init(&ctx->head);
        MD5_Update(&ctx->head, key, len);
        MD5_Final(hmac_key, &ctx->head);
    } else {
        memcpy(hmac_key, key, len);
    }

    for (i = 0; i < sizeof(hmac_key); i++)
        hmac_key[i] ^= 0x36; /* ipad */
    MD5_Init(&ctx->head);
    MD5_Update(&ctx->head, hmac_key, sizeof(hmac_key));

    for (i = 0; i < sizeof(hmac_key); i++)
        hmac_key[i] ^= 0x36 ^ 0x5c; /* opad */
    MD5_Init(&ctx->tail);
    MD5_Update(&ctx->tail, hmac_key, sizeof(hmac_key));

    OPENSSL_cleanse(hmac_key, sizeof(hmac_key));
}