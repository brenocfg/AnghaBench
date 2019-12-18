#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  digest; } ;
struct TYPE_8__ {unsigned char* outer_padding; TYPE_1__ ctx; } ;
typedef  TYPE_1__ MD5_CTX ;
typedef  TYPE_2__ HMAC_MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5Final (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Init (TYPE_1__*) ; 
 int /*<<< orphan*/  MD5Update (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

void HMACMD5Final(HMAC_MD5_CTX *ctx, unsigned char *digest)
{
    MD5_CTX outer_ctx;
    unsigned char inner_digest[16];

    MD5Final(&(ctx->ctx));
    memcpy(inner_digest, ctx->ctx.digest, 16);

    MD5Init(&outer_ctx);
    MD5Update(&outer_ctx, ctx->outer_padding, 64);
    MD5Update(&outer_ctx, inner_digest, 16);
    MD5Final(&outer_ctx);

    memcpy(digest, outer_ctx.digest, 16);
}