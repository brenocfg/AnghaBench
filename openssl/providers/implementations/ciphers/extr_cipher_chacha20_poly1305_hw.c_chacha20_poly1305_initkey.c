#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ text; scalar_t__ aad; } ;
struct TYPE_7__ {int /*<<< orphan*/  chacha; int /*<<< orphan*/  tls_payload_length; scalar_t__ mac_inited; scalar_t__ aad; TYPE_1__ len; } ;
struct TYPE_6__ {scalar_t__ enc; } ;
typedef  TYPE_2__ PROV_CIPHER_CTX ;
typedef  TYPE_3__ PROV_CHACHA20_POLY1305_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  NO_TLS_PAYLOAD_LENGTH ; 
 int chacha20_dinit (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int chacha20_einit (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chacha20_poly1305_initkey(PROV_CIPHER_CTX *bctx,
                                     const unsigned char *key, size_t keylen)
{
    PROV_CHACHA20_POLY1305_CTX *ctx = (PROV_CHACHA20_POLY1305_CTX *)bctx;

    ctx->len.aad = 0;
    ctx->len.text = 0;
    ctx->aad = 0;
    ctx->mac_inited = 0;
    ctx->tls_payload_length = NO_TLS_PAYLOAD_LENGTH;

    if (bctx->enc)
        return chacha20_einit(&ctx->chacha, key, keylen, NULL, 0);
    else
        return chacha20_dinit(&ctx->chacha, key, keylen, NULL, 0);
}