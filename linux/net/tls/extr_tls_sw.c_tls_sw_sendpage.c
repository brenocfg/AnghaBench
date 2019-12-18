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
struct tls_context {int /*<<< orphan*/  tx_lock; } ;
struct sock {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int MSG_DONTWAIT ; 
 int MSG_MORE ; 
 int MSG_NOSIGNAL ; 
 int MSG_SENDPAGE_NOPOLICY ; 
 int MSG_SENDPAGE_NOTLAST ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int tls_sw_do_sendpage (struct sock*,struct page*,int,size_t,int) ; 

int tls_sw_sendpage(struct sock *sk, struct page *page,
		    int offset, size_t size, int flags)
{
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	int ret;

	if (flags & ~(MSG_MORE | MSG_DONTWAIT | MSG_NOSIGNAL |
		      MSG_SENDPAGE_NOTLAST | MSG_SENDPAGE_NOPOLICY))
		return -ENOTSUPP;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);
	ret = tls_sw_do_sendpage(sk, page, offset, size, flags);
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	return ret;
}