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
struct tls_sw_context_rx {unsigned int (* sk_poll ) (struct file*,struct socket*,struct poll_table_struct*) ;scalar_t__ recv_pkt; } ;
struct tls_context {int dummy; } ;
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 unsigned int stub1 (struct file*,struct socket*,struct poll_table_struct*) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_sw_context_rx* tls_sw_ctx_rx (struct tls_context*) ; 

unsigned int tls_sw_poll(struct file *file, struct socket *sock,
			 struct poll_table_struct *wait)
{
	unsigned int ret;
	struct sock *sk = sock->sk;
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_sw_context_rx *ctx = tls_sw_ctx_rx(tls_ctx);

	/* Grab POLLOUT and POLLHUP from the underlying socket */
	ret = ctx->sk_poll(file, sock, wait);

	/* Clear POLLIN bits, and set based on recv_pkt */
	ret &= ~(POLLIN | POLLRDNORM);
	if (ctx->recv_pkt)
		ret |= POLLIN | POLLRDNORM;

	return ret;
}