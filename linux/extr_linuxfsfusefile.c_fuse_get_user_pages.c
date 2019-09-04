#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iov_iter {int type; } ;
struct TYPE_10__ {int argpages; TYPE_2__* args; } ;
struct TYPE_9__ {int argpages; TYPE_1__* args; } ;
struct fuse_req {scalar_t__ num_pages; scalar_t__ max_pages; TYPE_5__ out; TYPE_4__ in; TYPE_3__* page_descs; int /*<<< orphan*/ * pages; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_8__ {size_t offset; scalar_t__ length; } ;
struct TYPE_7__ {void* value; } ;
struct TYPE_6__ {void* value; } ;

/* Variables and functions */
 int ITER_KVEC ; 
 scalar_t__ PAGE_SIZE ; 
 size_t fuse_get_frag_size (struct iov_iter*,size_t) ; 
 unsigned long fuse_get_user_addr (struct iov_iter*) ; 
 int /*<<< orphan*/  fuse_page_descs_length_init (struct fuse_req*,size_t,unsigned int) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,scalar_t__) ; 
 scalar_t__ iov_iter_get_pages (struct iov_iter*,int /*<<< orphan*/ *,size_t,scalar_t__,size_t*) ; 

__attribute__((used)) static int fuse_get_user_pages(struct fuse_req *req, struct iov_iter *ii,
			       size_t *nbytesp, int write)
{
	size_t nbytes = 0;  /* # bytes already packed in req */
	ssize_t ret = 0;

	/* Special case for kernel I/O: can copy directly into the buffer */
	if (ii->type & ITER_KVEC) {
		unsigned long user_addr = fuse_get_user_addr(ii);
		size_t frag_size = fuse_get_frag_size(ii, *nbytesp);

		if (write)
			req->in.args[1].value = (void *) user_addr;
		else
			req->out.args[0].value = (void *) user_addr;

		iov_iter_advance(ii, frag_size);
		*nbytesp = frag_size;
		return 0;
	}

	while (nbytes < *nbytesp && req->num_pages < req->max_pages) {
		unsigned npages;
		size_t start;
		ret = iov_iter_get_pages(ii, &req->pages[req->num_pages],
					*nbytesp - nbytes,
					req->max_pages - req->num_pages,
					&start);
		if (ret < 0)
			break;

		iov_iter_advance(ii, ret);
		nbytes += ret;

		ret += start;
		npages = (ret + PAGE_SIZE - 1) / PAGE_SIZE;

		req->page_descs[req->num_pages].offset = start;
		fuse_page_descs_length_init(req, req->num_pages, npages);

		req->num_pages += npages;
		req->page_descs[req->num_pages - 1].length -=
			(PAGE_SIZE - ret) & (PAGE_SIZE - 1);
	}

	if (write)
		req->in.argpages = 1;
	else
		req->out.argpages = 1;

	*nbytesp = nbytes;

	return ret < 0 ? ret : 0;
}