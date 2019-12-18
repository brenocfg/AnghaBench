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
struct vmbus_channel {int /*<<< orphan*/  outbound; } ;
struct sock {int /*<<< orphan*/  (* sk_write_space ) (struct sock*) ;int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;} ;
struct hvsock {struct vmbus_channel* chan; } ;

/* Variables and functions */
 scalar_t__ hv_get_bytes_to_write (int /*<<< orphan*/ *) ; 
 scalar_t__ hvs_channel_readable (struct vmbus_channel*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void hvs_channel_cb(void *ctx)
{
	struct sock *sk = (struct sock *)ctx;
	struct vsock_sock *vsk = vsock_sk(sk);
	struct hvsock *hvs = vsk->trans;
	struct vmbus_channel *chan = hvs->chan;

	if (hvs_channel_readable(chan))
		sk->sk_data_ready(sk);

	if (hv_get_bytes_to_write(&chan->outbound) > 0)
		sk->sk_write_space(sk);
}