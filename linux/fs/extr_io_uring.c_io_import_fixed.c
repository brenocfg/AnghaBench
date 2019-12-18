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
typedef  size_t u64 ;
struct iov_iter {unsigned long nr_segs; size_t count; size_t iov_offset; struct bio_vec const* bvec; } ;
struct io_uring_sqe {int /*<<< orphan*/  addr; int /*<<< orphan*/  buf_index; int /*<<< orphan*/  len; } ;
struct io_ring_ctx {unsigned int nr_user_bufs; struct io_mapped_ubuf* user_bufs; } ;
struct io_mapped_ubuf {size_t ubuf; size_t len; struct bio_vec* bvec; int /*<<< orphan*/  nr_bvecs; } ;
struct bio_vec {size_t bv_len; } ;

/* Variables and functions */
 int EFAULT ; 
 size_t PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int array_index_nospec (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,size_t) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int,struct bio_vec*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int io_import_fixed(struct io_ring_ctx *ctx, int rw,
			   const struct io_uring_sqe *sqe,
			   struct iov_iter *iter)
{
	size_t len = READ_ONCE(sqe->len);
	struct io_mapped_ubuf *imu;
	unsigned index, buf_index;
	size_t offset;
	u64 buf_addr;

	/* attempt to use fixed buffers without having provided iovecs */
	if (unlikely(!ctx->user_bufs))
		return -EFAULT;

	buf_index = READ_ONCE(sqe->buf_index);
	if (unlikely(buf_index >= ctx->nr_user_bufs))
		return -EFAULT;

	index = array_index_nospec(buf_index, ctx->nr_user_bufs);
	imu = &ctx->user_bufs[index];
	buf_addr = READ_ONCE(sqe->addr);

	/* overflow */
	if (buf_addr + len < buf_addr)
		return -EFAULT;
	/* not inside the mapped region */
	if (buf_addr < imu->ubuf || buf_addr + len > imu->ubuf + imu->len)
		return -EFAULT;

	/*
	 * May not be a start of buffer, set size appropriately
	 * and advance us to the beginning.
	 */
	offset = buf_addr - imu->ubuf;
	iov_iter_bvec(iter, rw, imu->bvec, imu->nr_bvecs, offset + len);

	if (offset) {
		/*
		 * Don't use iov_iter_advance() here, as it's really slow for
		 * using the latter parts of a big fixed buffer - it iterates
		 * over each segment manually. We can cheat a bit here, because
		 * we know that:
		 *
		 * 1) it's a BVEC iter, we set it up
		 * 2) all bvecs are PAGE_SIZE in size, except potentially the
		 *    first and last bvec
		 *
		 * So just find our index, and adjust the iterator afterwards.
		 * If the offset is within the first bvec (or the whole first
		 * bvec, just use iov_iter_advance(). This makes it easier
		 * since we can just skip the first segment, which may not
		 * be PAGE_SIZE aligned.
		 */
		const struct bio_vec *bvec = imu->bvec;

		if (offset <= bvec->bv_len) {
			iov_iter_advance(iter, offset);
		} else {
			unsigned long seg_skip;

			/* skip first vec */
			offset -= bvec->bv_len;
			seg_skip = 1 + (offset >> PAGE_SHIFT);

			iter->bvec = bvec + seg_skip;
			iter->nr_segs -= seg_skip;
			iter->count -= bvec->bv_len + offset;
			iter->iov_offset = offset & ~PAGE_MASK;
		}
	}

	return 0;
}