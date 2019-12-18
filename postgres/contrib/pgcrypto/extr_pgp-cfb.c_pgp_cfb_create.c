#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_5__ {int resync; int /*<<< orphan*/  block_size; int /*<<< orphan*/  fr; int /*<<< orphan*/ * ciph; } ;
typedef  int /*<<< orphan*/  PX_Cipher ;
typedef  TYPE_1__ PGP_CFB ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pgp_load_cipher (int,int /*<<< orphan*/ **) ; 
 TYPE_1__* px_alloc (int) ; 
 int /*<<< orphan*/  px_cipher_block_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  px_cipher_free (int /*<<< orphan*/ *) ; 
 int px_cipher_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

int
pgp_cfb_create(PGP_CFB **ctx_p, int algo, const uint8 *key, int key_len,
			   int resync, uint8 *iv)
{
	int			res;
	PX_Cipher  *ciph;
	PGP_CFB    *ctx;

	res = pgp_load_cipher(algo, &ciph);
	if (res < 0)
		return res;

	res = px_cipher_init(ciph, key, key_len, NULL);
	if (res < 0)
	{
		px_cipher_free(ciph);
		return res;
	}

	ctx = px_alloc(sizeof(*ctx));
	memset(ctx, 0, sizeof(*ctx));
	ctx->ciph = ciph;
	ctx->block_size = px_cipher_block_size(ciph);
	ctx->resync = resync;

	if (iv)
		memcpy(ctx->fr, iv, ctx->block_size);

	*ctx_p = ctx;
	return 0;
}