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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/  sha256ctx; int /*<<< orphan*/ * k_opad; } ;
typedef  TYPE_1__ scram_HMAC_ctx ;

/* Variables and functions */
 int SCRAM_KEY_LEN ; 
 int SHA256_HMAC_B ; 
 int /*<<< orphan*/  pg_sha256_final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_sha256_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_sha256_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void
scram_HMAC_final(uint8 *result, scram_HMAC_ctx *ctx)
{
	uint8		h[SCRAM_KEY_LEN];

	pg_sha256_final(&ctx->sha256ctx, h);

	/* H(K XOR opad, tmp) */
	pg_sha256_init(&ctx->sha256ctx);
	pg_sha256_update(&ctx->sha256ctx, ctx->k_opad, SHA256_HMAC_B);
	pg_sha256_update(&ctx->sha256ctx, h, SCRAM_KEY_LEN);
	pg_sha256_final(&ctx->sha256ctx, result);
}