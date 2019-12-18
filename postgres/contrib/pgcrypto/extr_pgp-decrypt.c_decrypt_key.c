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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct TYPE_5__ {int sess_key_len; int /*<<< orphan*/  cipher_algo; int /*<<< orphan*/ * sess_key; TYPE_1__ s2k; int /*<<< orphan*/  s2k_cipher_algo; } ;
typedef  TYPE_2__ PGP_Context ;
typedef  int /*<<< orphan*/  PGP_CFB ;

/* Variables and functions */
 int PXE_PGP_CORRUPT_DATA ; 
 int pgp_cfb_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_cfb_decrypt (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgp_cfb_free (int /*<<< orphan*/ *) ; 
 int pgp_get_cipher_key_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_debug (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
decrypt_key(PGP_Context *ctx, const uint8 *src, int len)
{
	int			res;
	uint8		algo;
	PGP_CFB    *cfb;

	res = pgp_cfb_create(&cfb, ctx->s2k_cipher_algo,
						 ctx->s2k.key, ctx->s2k.key_len, 0, NULL);
	if (res < 0)
		return res;

	pgp_cfb_decrypt(cfb, src, 1, &algo);
	src++;
	len--;

	pgp_cfb_decrypt(cfb, src, len, ctx->sess_key);
	pgp_cfb_free(cfb);
	ctx->sess_key_len = len;
	ctx->cipher_algo = algo;

	if (pgp_get_cipher_key_size(algo) != len)
	{
		px_debug("sesskey bad len: algo=%d, expected=%d, got=%d",
				 algo, pgp_get_cipher_key_size(algo), len);
		return PXE_PGP_CORRUPT_DATA;
	}
	return 0;
}