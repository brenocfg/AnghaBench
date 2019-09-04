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
struct sock {int dummy; } ;
struct page {int dummy; } ;
struct kvec {char* iov_base; size_t iov_len; } ;
struct iov_iter {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int ITER_KVEC ; 
 int MSG_MORE ; 
 int MSG_OOB ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  TLS_RECORD_TYPE_DATA ; 
 int WRITE ; 
 int /*<<< orphan*/  iov_iter_kvec (struct iov_iter*,int,struct kvec*,int,size_t) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int tls_push_data (struct sock*,struct iov_iter*,size_t,int,int /*<<< orphan*/ ) ; 

int tls_device_sendpage(struct sock *sk, struct page *page,
			int offset, size_t size, int flags)
{
	struct iov_iter	msg_iter;
	char *kaddr = kmap(page);
	struct kvec iov;
	int rc;

	if (flags & MSG_SENDPAGE_NOTLAST)
		flags |= MSG_MORE;

	lock_sock(sk);

	if (flags & MSG_OOB) {
		rc = -ENOTSUPP;
		goto out;
	}

	iov.iov_base = kaddr + offset;
	iov.iov_len = size;
	iov_iter_kvec(&msg_iter, WRITE | ITER_KVEC, &iov, 1, size);
	rc = tls_push_data(sk, &msg_iter, size,
			   flags, TLS_RECORD_TYPE_DATA);
	kunmap(page);

out:
	release_sock(sk);
	return rc;
}