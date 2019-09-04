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
struct socket {int dummy; } ;
struct page {int dummy; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iter; } ;
struct bio_vec {int bv_offset; size_t bv_len; struct page* bv_page; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ITER_BVEC ; 
 int MSG_DONTWAIT ; 
 int MSG_EOR ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 int WRITE ; 
 int __ceph_tcp_sendpage (struct socket*,struct page*,int,size_t,int) ; 
 int /*<<< orphan*/  iov_iter_bvec (int /*<<< orphan*/ *,int,struct bio_vec*,int,size_t) ; 
 int page_count (struct page*) ; 
 int sock_sendmsg (struct socket*,struct msghdr*) ; 

__attribute__((used)) static int ceph_tcp_sendpage(struct socket *sock, struct page *page,
		     int offset, size_t size, bool more)
{
	struct msghdr msg = { .msg_flags = MSG_DONTWAIT | MSG_NOSIGNAL };
	struct bio_vec bvec;
	int ret;

	/*
	 * sendpage cannot properly handle pages with page_count == 0,
	 * we need to fall back to sendmsg if that's the case.
	 *
	 * Same goes for slab pages: skb_can_coalesce() allows
	 * coalescing neighboring slab objects into a single frag which
	 * triggers one of hardened usercopy checks.
	 */
	if (page_count(page) >= 1 && !PageSlab(page))
		return __ceph_tcp_sendpage(sock, page, offset, size, more);

	bvec.bv_page = page;
	bvec.bv_offset = offset;
	bvec.bv_len = size;

	if (more)
		msg.msg_flags |= MSG_MORE;
	else
		msg.msg_flags |= MSG_EOR;  /* superfluous, but what the hell */

	iov_iter_bvec(&msg.msg_iter, WRITE | ITER_BVEC, &bvec, 1, size);
	ret = sock_sendmsg(sock, &msg);
	if (ret == -EAGAIN)
		ret = 0;

	return ret;
}