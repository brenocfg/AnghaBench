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
typedef  size_t uint32_t ;
struct sha256_ctx {size_t buflen; void const* buffer; } ;

/* Variables and functions */
 scalar_t__ UNALIGNED_P (void const*) ; 
 void const* memcpy (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  sha256_process_block (void const*,int,struct sha256_ctx*) ; 

__attribute__((used)) static void sha256_process_bytes(const void *buffer, size_t len, struct sha256_ctx *ctx) {
	/* When we already have some bits in our internal buffer concatenate
	 both inputs first.  */
	if (ctx->buflen != 0) {
		size_t left_over = ctx->buflen;
		size_t add = 128 - left_over > len ? len : 128 - left_over;

		  memcpy(&ctx->buffer[left_over], buffer, add);
		  ctx->buflen += (uint32_t)add;

		if (ctx->buflen > 64) {
			sha256_process_block(ctx->buffer, ctx->buflen & ~63, ctx);
			ctx->buflen &= 63;
			/* The regions in the following copy operation cannot overlap.  */
			memcpy(ctx->buffer, &ctx->buffer[(left_over + add) & ~63], ctx->buflen);
		}

		buffer = (const char *) buffer + add;
		len -= add;
	}

	/* Process available complete blocks.  */
	if (len >= 64) {
/* To check alignment gcc has an appropriate operator.  Other
compilers don't.  */
#if __GNUC__ >= 2
# define UNALIGNED_P(p) (((uintptr_t) p) % __alignof__ (uint32_t) != 0)
#else
# define UNALIGNED_P(p) (((uintptr_t) p) % sizeof (uint32_t) != 0)
#endif
		if (UNALIGNED_P (buffer))
			while (len > 64) {
				sha256_process_block(memcpy(ctx->buffer, buffer, 64), 64, ctx);
				buffer = (const char *) buffer + 64;
				len -= 64;
			} else {
				sha256_process_block(buffer, len & ~63, ctx);
				buffer = (const char *) buffer + (len & ~63);
				len &= 63;
			}
	}

	/* Move remaining bytes into internal buffer.  */
	if (len > 0) {
		size_t left_over = ctx->buflen;

		memcpy(&ctx->buffer[left_over], buffer, len);
		left_over += len;
		if (left_over >= 64) {
			sha256_process_block(ctx->buffer, 64, ctx);
			left_over -= 64;
			memcpy(ctx->buffer, &ctx->buffer[64], left_over);
		}
		ctx->buflen = (uint32_t)left_over;
	}
}