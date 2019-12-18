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
struct TYPE_3__ {int block_no; int pos; int* encbuf; int* fre; int fr; int block_size; } ;
typedef  TYPE_1__ PGP_CFB ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,int*,int) ; 

__attribute__((used)) static int
mix_encrypt_resync(PGP_CFB *ctx, const uint8 *data, int len, uint8 *dst)
{
	int			i,
				n;

	/* block #2 is 2 bytes long */
	if (ctx->block_no == 2)
	{
		n = 2 - ctx->pos;
		if (len < n)
			n = len;
		for (i = ctx->pos; i < ctx->pos + n; i++)
			*dst++ = ctx->encbuf[i] = ctx->fre[i] ^ (*data++);

		ctx->pos += n;
		len -= n;

		if (ctx->pos == 2)
		{
			memcpy(ctx->fr, ctx->encbuf + 2, ctx->block_size - 2);
			memcpy(ctx->fr + ctx->block_size - 2, ctx->encbuf, 2);
			ctx->pos = 0;
			return n;
		}
	}
	for (i = ctx->pos; i < ctx->pos + len; i++)
		*dst++ = ctx->encbuf[i] = ctx->fre[i] ^ (*data++);
	ctx->pos += len;
	return len;
}