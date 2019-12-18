#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t lo; void const* buffer; scalar_t__ hi; } ;
typedef  TYPE_1__ MD5_CTX ;

/* Variables and functions */
 void* MD5_body (TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (void const*,void const*,size_t) ; 

__attribute__((used)) static void
MD5_hash(const void *data, size_t size, MD5_CTX *ctx)
{
	uint32_t saved_lo;
	unsigned long used, available;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		ctx->hi++;
	ctx->hi += size >> 29;

	used = saved_lo & 0x3f;

	if (used) {
		available = 64 - used;

		if (size < available) {
			memcpy(&ctx->buffer[used], data, size);
			return;
		}

		memcpy(&ctx->buffer[used], data, available);
		data = (const unsigned char *)data + available;
		size -= available;
		MD5_body(ctx, ctx->buffer, 64);
	}

	if (size >= 64) {
		data = MD5_body(ctx, data, size & ~((size_t) 0x3f));
		size &= 0x3f;
	}

	memcpy(ctx->buffer, data, size);
}