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
struct TYPE_3__ {int /*<<< orphan*/  sha256ctx; } ;
typedef  TYPE_1__ scram_HMAC_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  pg_sha256_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void
scram_HMAC_update(scram_HMAC_ctx *ctx, const char *str, int slen)
{
	pg_sha256_update(&ctx->sha256ctx, (const uint8 *) str, slen);
}