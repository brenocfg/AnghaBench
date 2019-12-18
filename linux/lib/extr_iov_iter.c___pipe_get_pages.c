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
struct pipe_inode_info {TYPE_1__* bufs; } ;
struct page {int dummy; } ;
struct iov_iter {struct pipe_inode_info* pipe; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 size_t EFAULT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int next_idx (int,struct pipe_inode_info*) ; 
 size_t push_pipe (struct iov_iter*,size_t,int*,size_t*) ; 

__attribute__((used)) static inline ssize_t __pipe_get_pages(struct iov_iter *i,
				size_t maxsize,
				struct page **pages,
				int idx,
				size_t *start)
{
	struct pipe_inode_info *pipe = i->pipe;
	ssize_t n = push_pipe(i, maxsize, &idx, start);
	if (!n)
		return -EFAULT;

	maxsize = n;
	n += *start;
	while (n > 0) {
		get_page(*pages++ = pipe->bufs[idx].page);
		idx = next_idx(idx, pipe);
		n -= PAGE_SIZE;
	}

	return maxsize;
}