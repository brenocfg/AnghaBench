#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  c; } ;
struct TYPE_6__ {TYPE_1__ Xi; } ;
typedef  TYPE_2__ GCM128_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_gcm128_finish (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,size_t) ; 

void CRYPTO_gcm128_tag(GCM128_CONTEXT *ctx, unsigned char *tag, size_t len)
{
    CRYPTO_gcm128_finish(ctx, NULL, 0);
    memcpy(tag, ctx->Xi.c,
           len <= sizeof(ctx->Xi.c) ? len : sizeof(ctx->Xi.c));
}