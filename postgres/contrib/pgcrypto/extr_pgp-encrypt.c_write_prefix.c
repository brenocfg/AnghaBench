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
struct TYPE_3__ {int /*<<< orphan*/  cipher_algo; } ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  TYPE_1__ PGP_Context ;

/* Variables and functions */
 int /*<<< orphan*/  PGP_MAX_BLOCK ; 
 int PXE_NO_RANDOM ; 
 int /*<<< orphan*/  pg_strong_random (int /*<<< orphan*/ *,int) ; 
 int pgp_get_cipher_block_size (int /*<<< orphan*/ ) ; 
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  px_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
write_prefix(PGP_Context *ctx, PushFilter *dst)
{
	uint8		prefix[PGP_MAX_BLOCK + 2];
	int			res,
				bs;

	bs = pgp_get_cipher_block_size(ctx->cipher_algo);
	if (!pg_strong_random(prefix, bs))
		return PXE_NO_RANDOM;

	prefix[bs + 0] = prefix[bs - 2];
	prefix[bs + 1] = prefix[bs - 1];

	res = pushf_write(dst, prefix, bs + 2);
	px_memset(prefix, 0, bs + 2);
	return res < 0 ? res : 0;
}