#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {TYPE_1__ s2k; int /*<<< orphan*/  sess_key; int /*<<< orphan*/  sess_key_len; int /*<<< orphan*/  cipher_algo; scalar_t__ pub_key; scalar_t__ use_sess_key; } ;
typedef  TYPE_2__ PGP_Context ;

/* Variables and functions */
 int PXE_NO_RANDOM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_strong_random (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgp_get_cipher_key_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
init_sess_key(PGP_Context *ctx)
{
	if (ctx->use_sess_key || ctx->pub_key)
	{
		ctx->sess_key_len = pgp_get_cipher_key_size(ctx->cipher_algo);
		if (!pg_strong_random(ctx->sess_key, ctx->sess_key_len))
			return PXE_NO_RANDOM;
	}
	else
	{
		ctx->sess_key_len = ctx->s2k.key_len;
		memcpy(ctx->sess_key, ctx->s2k.key, ctx->s2k.key_len);
	}

	return 0;
}