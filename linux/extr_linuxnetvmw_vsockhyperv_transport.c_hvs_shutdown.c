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
struct vsock_sock {struct hvsock* trans; } ;
struct vmpipe_proto_header {int dummy; } ;
struct sock {int dummy; } ;
struct hvsock {int fin_sent; int /*<<< orphan*/  chan; } ;
struct hvs_send_buf {int dummy; } ;

/* Variables and functions */
 int SEND_SHUTDOWN ; 
 int /*<<< orphan*/  hvs_send_data (int /*<<< orphan*/ ,struct hvs_send_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 struct sock* sk_vsock (struct vsock_sock*) ; 

__attribute__((used)) static int hvs_shutdown(struct vsock_sock *vsk, int mode)
{
	struct sock *sk = sk_vsock(vsk);
	struct vmpipe_proto_header hdr;
	struct hvs_send_buf *send_buf;
	struct hvsock *hvs;

	if (!(mode & SEND_SHUTDOWN))
		return 0;

	lock_sock(sk);

	hvs = vsk->trans;
	if (hvs->fin_sent)
		goto out;

	send_buf = (struct hvs_send_buf *)&hdr;

	/* It can't fail: see hvs_channel_writable_bytes(). */
	(void)hvs_send_data(hvs->chan, send_buf, 0);

	hvs->fin_sent = true;
out:
	release_sock(sk);
	return 0;
}