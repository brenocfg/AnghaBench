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
typedef  size_t u32 ;
struct btrfsic_block_data_ctx {size_t start; size_t len; char** datav; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long DIV_ROUND_UP (size_t,scalar_t__) ; 
 size_t PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t min (size_t,size_t) ; 
 size_t offset_in_page (size_t) ; 

__attribute__((used)) static void btrfsic_read_from_block_data(
	struct btrfsic_block_data_ctx *block_ctx,
	void *dstv, u32 offset, size_t len)
{
	size_t cur;
	size_t pgoff;
	char *kaddr;
	char *dst = (char *)dstv;
	size_t start_offset = offset_in_page(block_ctx->start);
	unsigned long i = (start_offset + offset) >> PAGE_SHIFT;

	WARN_ON(offset + len > block_ctx->len);
	pgoff = offset_in_page(start_offset + offset);

	while (len > 0) {
		cur = min(len, ((size_t)PAGE_SIZE - pgoff));
		BUG_ON(i >= DIV_ROUND_UP(block_ctx->len, PAGE_SIZE));
		kaddr = block_ctx->datav[i];
		memcpy(dst, kaddr + pgoff, cur);

		dst += cur;
		len -= cur;
		pgoff = 0;
		i++;
	}
}