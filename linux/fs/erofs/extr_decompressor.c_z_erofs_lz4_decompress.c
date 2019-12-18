#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct z_erofs_decompress_req {unsigned int inputsize; scalar_t__* in; unsigned int outputsize; scalar_t__* out; int /*<<< orphan*/  sb; scalar_t__ partial_decoding; int /*<<< orphan*/  pageofs_out; scalar_t__ inplace_io; } ;
struct TYPE_2__ {int feature_incompat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EROFS_FEATURE_INCOMPAT_LZ4_0PADDING ; 
 TYPE_1__* EROFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int const LZ4_DECOMPRESS_INPLACE_MARGIN (unsigned int) ; 
 int LZ4_decompress_safe_partial (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int) ; 
 int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 unsigned int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  erofs_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  erofs_put_pcpubuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * generic_copy_inplace_data (struct z_erofs_decompress_req*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * kmap_atomic (scalar_t__) ; 
 int /*<<< orphan*/  kunmap_atomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int z_erofs_lz4_decompress(struct z_erofs_decompress_req *rq, u8 *out)
{
	unsigned int inputmargin, inlen;
	u8 *src;
	bool copied, support_0padding;
	int ret;

	if (rq->inputsize > PAGE_SIZE)
		return -EOPNOTSUPP;

	src = kmap_atomic(*rq->in);
	inputmargin = 0;
	support_0padding = false;

	/* decompression inplace is only safe when 0padding is enabled */
	if (EROFS_SB(rq->sb)->feature_incompat &
	    EROFS_FEATURE_INCOMPAT_LZ4_0PADDING) {
		support_0padding = true;

		while (!src[inputmargin & ~PAGE_MASK])
			if (!(++inputmargin & ~PAGE_MASK))
				break;

		if (inputmargin >= rq->inputsize) {
			kunmap_atomic(src);
			return -EIO;
		}
	}

	copied = false;
	inlen = rq->inputsize - inputmargin;
	if (rq->inplace_io) {
		const uint oend = (rq->pageofs_out +
				   rq->outputsize) & ~PAGE_MASK;
		const uint nr = PAGE_ALIGN(rq->pageofs_out +
					   rq->outputsize) >> PAGE_SHIFT;

		if (rq->partial_decoding || !support_0padding ||
		    rq->out[nr - 1] != rq->in[0] ||
		    rq->inputsize - oend <
		      LZ4_DECOMPRESS_INPLACE_MARGIN(inlen)) {
			src = generic_copy_inplace_data(rq, src, inputmargin);
			inputmargin = 0;
			copied = true;
		}
	}

	ret = LZ4_decompress_safe_partial(src + inputmargin, out,
					  inlen, rq->outputsize,
					  rq->outputsize);
	if (ret < 0) {
		erofs_err(rq->sb, "failed to decompress, in[%u, %u] out[%u]",
			  inlen, inputmargin, rq->outputsize);
		WARN_ON(1);
		print_hex_dump(KERN_DEBUG, "[ in]: ", DUMP_PREFIX_OFFSET,
			       16, 1, src + inputmargin, inlen, true);
		print_hex_dump(KERN_DEBUG, "[out]: ", DUMP_PREFIX_OFFSET,
			       16, 1, out, rq->outputsize, true);
		ret = -EIO;
	}

	if (copied)
		erofs_put_pcpubuf(src);
	else
		kunmap_atomic(src);
	return ret;
}