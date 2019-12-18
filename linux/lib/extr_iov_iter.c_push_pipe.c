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
struct pipe_inode_info {int curbuf; TYPE_1__* bufs; int /*<<< orphan*/  nrbufs; } ;
struct page {int dummy; } ;
struct iov_iter {size_t count; struct pipe_inode_info* pipe; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {size_t len; scalar_t__ offset; struct page* page; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_USER ; 
 size_t PAGE_SIZE ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_start (struct iov_iter*,int*,size_t*) ; 
 int /*<<< orphan*/  default_pipe_buf_ops ; 
 int next_idx (int,struct pipe_inode_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static size_t push_pipe(struct iov_iter *i, size_t size,
			int *idxp, size_t *offp)
{
	struct pipe_inode_info *pipe = i->pipe;
	size_t off;
	int idx;
	ssize_t left;

	if (unlikely(size > i->count))
		size = i->count;
	if (unlikely(!size))
		return 0;

	left = size;
	data_start(i, &idx, &off);
	*idxp = idx;
	*offp = off;
	if (off) {
		left -= PAGE_SIZE - off;
		if (left <= 0) {
			pipe->bufs[idx].len += size;
			return size;
		}
		pipe->bufs[idx].len = PAGE_SIZE;
		idx = next_idx(idx, pipe);
	}
	while (idx != pipe->curbuf || !pipe->nrbufs) {
		struct page *page = alloc_page(GFP_USER);
		if (!page)
			break;
		pipe->nrbufs++;
		pipe->bufs[idx].ops = &default_pipe_buf_ops;
		pipe->bufs[idx].page = page;
		pipe->bufs[idx].offset = 0;
		if (left <= PAGE_SIZE) {
			pipe->bufs[idx].len = left;
			return size;
		}
		pipe->bufs[idx].len = PAGE_SIZE;
		left -= PAGE_SIZE;
		idx = next_idx(idx, pipe);
	}
	return size - left;
}