#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct arc4_ctx {int x; int* S; scalar_t__ y; } ;

/* Variables and functions */

int arc4_setkey(struct arc4_ctx *ctx, const u8 *in_key, unsigned int key_len)
{
	int i, j = 0, k = 0;

	ctx->x = 1;
	ctx->y = 0;

	for (i = 0; i < 256; i++)
		ctx->S[i] = i;

	for (i = 0; i < 256; i++) {
		u32 a = ctx->S[i];

		j = (j + in_key[k] + a) & 0xff;
		ctx->S[i] = ctx->S[j];
		ctx->S[j] = a;
		if (++k >= key_len)
			k = 0;
	}

	return 0;
}