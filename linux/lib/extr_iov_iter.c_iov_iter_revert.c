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
struct pipe_inode_info {int buffers; TYPE_1__* bufs; } ;
typedef  struct iovec {size_t iov_len; } const iovec ;
struct iov_iter {size_t count; int idx; size_t iov_offset; int start_idx; struct iovec const* iov; int /*<<< orphan*/  nr_segs; struct bio_vec const* bvec; struct pipe_inode_info* pipe; } ;
typedef  struct bio_vec {size_t bv_len; } const bio_vec ;
struct TYPE_2__ {size_t offset; size_t len; } ;

/* Variables and functions */
 size_t MAX_RW_COUNT ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ iov_iter_is_bvec (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_is_discard (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_is_pipe (struct iov_iter*) ; 
 int /*<<< orphan*/  pipe_truncate (struct iov_iter*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void iov_iter_revert(struct iov_iter *i, size_t unroll)
{
	if (!unroll)
		return;
	if (WARN_ON(unroll > MAX_RW_COUNT))
		return;
	i->count += unroll;
	if (unlikely(iov_iter_is_pipe(i))) {
		struct pipe_inode_info *pipe = i->pipe;
		int idx = i->idx;
		size_t off = i->iov_offset;
		while (1) {
			size_t n = off - pipe->bufs[idx].offset;
			if (unroll < n) {
				off -= unroll;
				break;
			}
			unroll -= n;
			if (!unroll && idx == i->start_idx) {
				off = 0;
				break;
			}
			if (!idx--)
				idx = pipe->buffers - 1;
			off = pipe->bufs[idx].offset + pipe->bufs[idx].len;
		}
		i->iov_offset = off;
		i->idx = idx;
		pipe_truncate(i);
		return;
	}
	if (unlikely(iov_iter_is_discard(i)))
		return;
	if (unroll <= i->iov_offset) {
		i->iov_offset -= unroll;
		return;
	}
	unroll -= i->iov_offset;
	if (iov_iter_is_bvec(i)) {
		const struct bio_vec *bvec = i->bvec;
		while (1) {
			size_t n = (--bvec)->bv_len;
			i->nr_segs++;
			if (unroll <= n) {
				i->bvec = bvec;
				i->iov_offset = n - unroll;
				return;
			}
			unroll -= n;
		}
	} else { /* same logics for iovec and kvec */
		const struct iovec *iov = i->iov;
		while (1) {
			size_t n = (--iov)->iov_len;
			i->nr_segs++;
			if (unroll <= n) {
				i->iov = iov;
				i->iov_offset = n - unroll;
				return;
			}
			unroll -= n;
		}
	}
}