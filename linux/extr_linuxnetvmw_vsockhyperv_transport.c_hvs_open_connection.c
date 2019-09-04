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
typedef  void* uuid_le ;
struct sockaddr_vm {int dummy; } ;
struct vsock_sock {struct sockaddr_vm local_addr; int /*<<< orphan*/  remote_addr; struct hvsock* trans; } ;
struct TYPE_6__ {unsigned char* user_def; } ;
struct TYPE_7__ {TYPE_1__ pipe; } ;
struct TYPE_8__ {void* if_type; void* if_instance; TYPE_2__ u; } ;
struct TYPE_9__ {TYPE_3__ offer; } ;
struct vmbus_channel {TYPE_4__ offermsg; } ;
struct sock {scalar_t__ sk_state; scalar_t__ sk_ack_backlog; scalar_t__ sk_max_ack_backlog; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;TYPE_5__* sk_socket; int /*<<< orphan*/  sk_type; } ;
struct hvsock {void* host_srv_id; void* vm_srv_id; struct vmbus_channel* chan; } ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HV_CALL_DIRECT ; 
 scalar_t__ MAX_LISTEN_PORT ; 
 int /*<<< orphan*/  RINGBUFFER_HVS_RCV_SIZE ; 
 int /*<<< orphan*/  RINGBUFFER_HVS_SND_SIZE ; 
 int /*<<< orphan*/  SS_CONNECTED ; 
 void* TCP_ESTABLISHED ; 
 scalar_t__ TCP_LISTEN ; 
 scalar_t__ TCP_SYN_SENT ; 
 struct sock* __vsock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_port_by_srv_id (void**) ; 
 int /*<<< orphan*/  hvs_addr_init (struct sockaddr_vm*,void**) ; 
 int /*<<< orphan*/  hvs_channel_cb ; 
 int /*<<< orphan*/  hvs_close_connection ; 
 int /*<<< orphan*/  hvs_remote_addr_init (int /*<<< orphan*/ *,struct sockaddr_vm*) ; 
 int /*<<< orphan*/  is_valid_srv_id (void**) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int /*<<< orphan*/  set_channel_read_mode (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_per_channel_state (struct vmbus_channel*,struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int vmbus_open (struct vmbus_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sock*) ; 
 int /*<<< orphan*/  vmbus_set_chn_rescind_callback (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsock_enqueue_accept (struct sock*,struct sock*) ; 
 struct sock* vsock_find_bound_socket (struct sockaddr_vm*) ; 
 int /*<<< orphan*/  vsock_insert_connected (struct vsock_sock*) ; 
 struct vsock_sock* vsock_sk (struct sock*) ; 

__attribute__((used)) static void hvs_open_connection(struct vmbus_channel *chan)
{
	uuid_le *if_instance, *if_type;
	unsigned char conn_from_host;

	struct sockaddr_vm addr;
	struct sock *sk, *new = NULL;
	struct vsock_sock *vnew;
	struct hvsock *hvs, *hvs_new;
	int ret;

	if_type = &chan->offermsg.offer.if_type;
	if_instance = &chan->offermsg.offer.if_instance;
	conn_from_host = chan->offermsg.offer.u.pipe.user_def[0];

	/* The host or the VM should only listen on a port in
	 * [0, MAX_LISTEN_PORT]
	 */
	if (!is_valid_srv_id(if_type) ||
	    get_port_by_srv_id(if_type) > MAX_LISTEN_PORT)
		return;

	hvs_addr_init(&addr, conn_from_host ? if_type : if_instance);
	sk = vsock_find_bound_socket(&addr);
	if (!sk)
		return;

	lock_sock(sk);
	if ((conn_from_host && sk->sk_state != TCP_LISTEN) ||
	    (!conn_from_host && sk->sk_state != TCP_SYN_SENT))
		goto out;

	if (conn_from_host) {
		if (sk->sk_ack_backlog >= sk->sk_max_ack_backlog)
			goto out;

		new = __vsock_create(sock_net(sk), NULL, sk, GFP_KERNEL,
				     sk->sk_type, 0);
		if (!new)
			goto out;

		new->sk_state = TCP_SYN_SENT;
		vnew = vsock_sk(new);
		hvs_new = vnew->trans;
		hvs_new->chan = chan;
	} else {
		hvs = vsock_sk(sk)->trans;
		hvs->chan = chan;
	}

	set_channel_read_mode(chan, HV_CALL_DIRECT);
	ret = vmbus_open(chan, RINGBUFFER_HVS_SND_SIZE,
			 RINGBUFFER_HVS_RCV_SIZE, NULL, 0,
			 hvs_channel_cb, conn_from_host ? new : sk);
	if (ret != 0) {
		if (conn_from_host) {
			hvs_new->chan = NULL;
			sock_put(new);
		} else {
			hvs->chan = NULL;
		}
		goto out;
	}

	set_per_channel_state(chan, conn_from_host ? new : sk);
	vmbus_set_chn_rescind_callback(chan, hvs_close_connection);

	if (conn_from_host) {
		new->sk_state = TCP_ESTABLISHED;
		sk->sk_ack_backlog++;

		hvs_addr_init(&vnew->local_addr, if_type);
		hvs_remote_addr_init(&vnew->remote_addr, &vnew->local_addr);

		hvs_new->vm_srv_id = *if_type;
		hvs_new->host_srv_id = *if_instance;

		vsock_insert_connected(vnew);

		vsock_enqueue_accept(sk, new);
	} else {
		sk->sk_state = TCP_ESTABLISHED;
		sk->sk_socket->state = SS_CONNECTED;

		vsock_insert_connected(vsock_sk(sk));
	}

	sk->sk_state_change(sk);

out:
	/* Release refcnt obtained when we called vsock_find_bound_socket() */
	sock_put(sk);

	release_sock(sk);
}