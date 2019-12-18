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
struct TYPE_3__ {scalar_t__ s2k_cipher_algo; scalar_t__ cipher_algo; int /*<<< orphan*/  sym_key_len; int /*<<< orphan*/  sym_key; int /*<<< orphan*/  s2k; int /*<<< orphan*/  s2k_count; int /*<<< orphan*/  s2k_digest_algo; int /*<<< orphan*/  s2k_mode; } ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int pgp_s2k_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pgp_s2k_process (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_s2k_key(PGP_Context *ctx)
{
	int			res;

	if (ctx->s2k_cipher_algo < 0)
		ctx->s2k_cipher_algo = ctx->cipher_algo;

	res = pgp_s2k_fill(&ctx->s2k, ctx->s2k_mode, ctx->s2k_digest_algo, ctx->s2k_count);
	if (res < 0)
		return res;

	return pgp_s2k_process(&ctx->s2k, ctx->s2k_cipher_algo,
						   ctx->sym_key, ctx->sym_key_len);
}