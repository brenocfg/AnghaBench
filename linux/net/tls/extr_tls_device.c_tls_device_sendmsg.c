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
struct msghdr {int /*<<< orphan*/  msg_flags; int /*<<< orphan*/  msg_iter; int /*<<< orphan*/  msg_controllen; } ;

/* Variables and functions */
 unsigned char TLS_RECORD_TYPE_DATA ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 int tls_proccess_cmsg (struct sock*,struct msghdr*,unsigned char*) ; 
 int tls_push_data (struct sock*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int tls_device_sendmsg(struct sock *sk, struct msghdr *msg, size_t size)
{
	unsigned char record_type = TLS_RECORD_TYPE_DATA;
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	int rc;

	mutex_lock(&tls_ctx->tx_lock);
	lock_sock(sk);

	if (unlikely(msg->msg_controllen)) {
		rc = tls_proccess_cmsg(sk, msg, &record_type);
		if (rc)
			goto out;
	}

	rc = tls_push_data(sk, &msg->msg_iter, size,
			   msg->msg_flags, record_type);

out:
	release_sock(sk);
	mutex_unlock(&tls_ctx->tx_lock);
	return rc;
}