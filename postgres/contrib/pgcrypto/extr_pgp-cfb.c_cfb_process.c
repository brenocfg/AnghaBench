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
typedef  int (* mix_data_t ) (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ;
struct TYPE_5__ {scalar_t__ pos; int block_size; int block_no; int /*<<< orphan*/  encbuf; int /*<<< orphan*/  fr; int /*<<< orphan*/  fre; int /*<<< orphan*/  ciph; } ;
typedef  TYPE_1__ PGP_CFB ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  px_cipher_encrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cfb_process(PGP_CFB *ctx, const uint8 *data, int len, uint8 *dst,
			mix_data_t mix_data)
{
	int			n;
	int			res;

	while (len > 0 && ctx->pos > 0)
	{
		n = ctx->block_size - ctx->pos;
		if (len < n)
			n = len;

		n = mix_data(ctx, data, n, dst);
		data += n;
		dst += n;
		len -= n;

		if (ctx->pos == ctx->block_size)
		{
			memcpy(ctx->fr, ctx->encbuf, ctx->block_size);
			ctx->pos = 0;
		}
	}

	while (len > 0)
	{
		px_cipher_encrypt(ctx->ciph, ctx->fr, ctx->block_size, ctx->fre);
		if (ctx->block_no < 5)
			ctx->block_no++;

		n = ctx->block_size;
		if (len < n)
			n = len;

		res = mix_data(ctx, data, n, dst);
		data += res;
		dst += res;
		len -= res;

		if (ctx->pos == ctx->block_size)
		{
			memcpy(ctx->fr, ctx->encbuf, ctx->block_size);
			ctx->pos = 0;
		}
	}
	return 0;
}