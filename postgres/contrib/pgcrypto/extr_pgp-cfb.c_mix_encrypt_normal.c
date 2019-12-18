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
struct TYPE_3__ {int pos; int* encbuf; int* fre; } ;
typedef  TYPE_1__ PGP_CFB ;

/* Variables and functions */

__attribute__((used)) static int
mix_encrypt_normal(PGP_CFB *ctx, const uint8 *data, int len, uint8 *dst)
{
	int			i;

	for (i = ctx->pos; i < ctx->pos + len; i++)
		*dst++ = ctx->encbuf[i] = ctx->fre[i] ^ (*data++);
	ctx->pos += len;
	return len;
}