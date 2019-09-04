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
struct xdr_buf {unsigned int len; unsigned int page_len; TYPE_1__* tail; TYPE_1__* head; } ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {unsigned int iov_len; } ;

/* Variables and functions */
 int ENOTSOCK ; 
 scalar_t__ unlikely (int) ; 
 int xs_send_kvec (struct socket*,struct sockaddr*,int,TYPE_1__*,unsigned int,int) ; 
 int xs_send_pagedata (struct socket*,struct xdr_buf*,unsigned int,int,int,int*) ; 

__attribute__((used)) static int xs_sendpages(struct socket *sock, struct sockaddr *addr, int addrlen, struct xdr_buf *xdr, unsigned int base, bool zerocopy, int *sent_p)
{
	unsigned int remainder = xdr->len - base;
	int err = 0;
	int sent = 0;

	if (unlikely(!sock))
		return -ENOTSOCK;

	if (base != 0) {
		addr = NULL;
		addrlen = 0;
	}

	if (base < xdr->head[0].iov_len || addr != NULL) {
		unsigned int len = xdr->head[0].iov_len - base;
		remainder -= len;
		err = xs_send_kvec(sock, addr, addrlen, &xdr->head[0], base, remainder != 0);
		if (remainder == 0 || err != len)
			goto out;
		*sent_p += err;
		base = 0;
	} else
		base -= xdr->head[0].iov_len;

	if (base < xdr->page_len) {
		unsigned int len = xdr->page_len - base;
		remainder -= len;
		err = xs_send_pagedata(sock, xdr, base, remainder != 0, zerocopy, &sent);
		*sent_p += sent;
		if (remainder == 0 || sent != len)
			goto out;
		base = 0;
	} else
		base -= xdr->page_len;

	if (base >= xdr->tail[0].iov_len)
		return 0;
	err = xs_send_kvec(sock, NULL, 0, &xdr->tail[0], base, 0);
out:
	if (err > 0) {
		*sent_p += err;
		err = 0;
	}
	return err;
}