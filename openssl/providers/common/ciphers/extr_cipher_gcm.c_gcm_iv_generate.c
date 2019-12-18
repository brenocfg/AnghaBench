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
struct TYPE_3__ {int ivlen; int iv_gen_rand; int /*<<< orphan*/  iv_state; scalar_t__ iv; int /*<<< orphan*/  libctx; } ;
typedef  TYPE_1__ PROV_GCM_CTX ;

/* Variables and functions */
 int GCM_IV_DEFAULT_SIZE ; 
 int /*<<< orphan*/  IV_STATE_BUFFERED ; 
 scalar_t__ rand_bytes_ex (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int gcm_iv_generate(PROV_GCM_CTX *ctx, int offset)
{
    int sz = ctx->ivlen - offset;

    /* Must be at least 96 bits */
    if (sz <= 0 || ctx->ivlen < GCM_IV_DEFAULT_SIZE)
        return 0;

    /* Use DRBG to generate random iv */
    if (rand_bytes_ex(ctx->libctx, ctx->iv + offset, sz) <= 0)
        return 0;
    ctx->iv_state = IV_STATE_BUFFERED;
    ctx->iv_gen_rand = 1;
    return 1;
}