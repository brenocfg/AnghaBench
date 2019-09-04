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
typedef  int uint32_t ;
struct sha256_ctx {int buflen; int* total; int* H; int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int SWAP (int) ; 
 int /*<<< orphan*/  fillbuf ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sha256_process_block (int /*<<< orphan*/ *,int,struct sha256_ctx*) ; 

__attribute__((used)) static void * sha256_finish_ctx(struct sha256_ctx *ctx, void *resbuf) {
	/* Take yet unprocessed bytes into account.  */
	uint32_t bytes = ctx->buflen;
	size_t pad;
	unsigned int i;

	/* Now count remaining bytes.  */
	ctx->total[0] += bytes;
	if (ctx->total[0] < bytes) {
		++ctx->total[1];
	}

	pad = bytes >= 56 ? 64 + 56 - bytes : 56 - bytes;
	memcpy(&ctx->buffer[bytes], fillbuf, pad);

	/* Put the 64-bit file length in *bits* at the end of the buffer.  */
	*(uint32_t *) &ctx->buffer[bytes + pad + 4] = SWAP (ctx->total[0] << 3);
	*(uint32_t *) &ctx->buffer[bytes + pad] = SWAP ((ctx->total[1] << 3) |
						  (ctx->total[0] >> 29));

	/* Process last bytes.  */
	sha256_process_block(ctx->buffer, bytes + pad + 8, ctx);

	/* Put result from CTX in first 32 bytes following RESBUF.  */
	for (i = 0; i < 8; ++i) {
		((uint32_t *) resbuf)[i] = SWAP(ctx->H[i]);
	}

	return resbuf;
}