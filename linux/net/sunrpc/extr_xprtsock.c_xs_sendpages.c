#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xdr_buf {unsigned int len; unsigned int page_len; TYPE_1__* tail; TYPE_1__* head; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct msghdr {int msg_namelen; int msg_flags; struct sockaddr* msg_name; } ;
typedef  int /*<<< orphan*/  rpc_fraghdr ;
typedef  int /*<<< orphan*/  rm ;
struct TYPE_3__ {unsigned int iov_len; } ;

/* Variables and functions */
 int ENOTSOCK ; 
 int MSG_MORE ; 
 int XS_SENDMSG_FLAGS ; 
 scalar_t__ unlikely (int) ; 
 int xs_send_kvec (struct socket*,struct msghdr*,TYPE_1__*,unsigned int) ; 
 int xs_send_pagedata (struct socket*,struct msghdr*,struct xdr_buf*,unsigned int) ; 
 int xs_send_rm_and_kvec (struct socket*,struct msghdr*,int /*<<< orphan*/ ,TYPE_1__*,unsigned int) ; 

__attribute__((used)) static int xs_sendpages(struct socket *sock, struct sockaddr *addr, int addrlen, struct xdr_buf *xdr, unsigned int base, rpc_fraghdr rm, int *sent_p)
{
	struct msghdr msg = {
		.msg_name = addr,
		.msg_namelen = addrlen,
		.msg_flags = XS_SENDMSG_FLAGS | MSG_MORE,
	};
	unsigned int rmsize = rm ? sizeof(rm) : 0;
	unsigned int remainder = rmsize + xdr->len - base;
	unsigned int want;
	int err = 0;

	if (unlikely(!sock))
		return -ENOTSOCK;

	want = xdr->head[0].iov_len + rmsize;
	if (base < want) {
		unsigned int len = want - base;
		remainder -= len;
		if (remainder == 0)
			msg.msg_flags &= ~MSG_MORE;
		if (rmsize)
			err = xs_send_rm_and_kvec(sock, &msg, rm,
					&xdr->head[0], base);
		else
			err = xs_send_kvec(sock, &msg, &xdr->head[0], base);
		if (remainder == 0 || err != len)
			goto out;
		*sent_p += err;
		base = 0;
	} else
		base -= want;

	if (base < xdr->page_len) {
		unsigned int len = xdr->page_len - base;
		remainder -= len;
		if (remainder == 0)
			msg.msg_flags &= ~MSG_MORE;
		err = xs_send_pagedata(sock, &msg, xdr, base);
		if (remainder == 0 || err != len)
			goto out;
		*sent_p += err;
		base = 0;
	} else
		base -= xdr->page_len;

	if (base >= xdr->tail[0].iov_len)
		return 0;
	msg.msg_flags &= ~MSG_MORE;
	err = xs_send_kvec(sock, &msg, &xdr->tail[0], base);
out:
	if (err > 0) {
		*sent_p += err;
		err = 0;
	}
	return err;
}