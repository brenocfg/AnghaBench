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
struct TYPE_3__ {int /*<<< orphan*/  taglen; int /*<<< orphan*/  gcm; scalar_t__ enc; } ;
typedef  TYPE_1__ PROV_GCM_CTX ;

/* Variables and functions */
 scalar_t__ CRYPTO_gcm128_finish (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_gcm128_tag (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GCM_TAG_MAX_SIZE ; 

int gcm_cipher_final(PROV_GCM_CTX *ctx, unsigned char *tag)
{
    if (ctx->enc) {
        CRYPTO_gcm128_tag(&ctx->gcm, tag, GCM_TAG_MAX_SIZE);
        ctx->taglen = GCM_TAG_MAX_SIZE;
    } else {
        if (CRYPTO_gcm128_finish(&ctx->gcm, tag, ctx->taglen) != 0)
            return 0;
    }
    return 1;
}