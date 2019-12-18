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
struct TYPE_2__ {int /*<<< orphan*/  deferredq; } ;
struct tipc_msg {int dummy; } ;
struct tipc_sock {int group_is_open; TYPE_1__ mc_method; int /*<<< orphan*/  snd_win; int /*<<< orphan*/  rcv_win; int /*<<< orphan*/  dupl_rcvcnt; int /*<<< orphan*/  conn_timeout; int /*<<< orphan*/  portid; struct tipc_msg phdr; int /*<<< orphan*/  cong_links; int /*<<< orphan*/  publications; int /*<<< orphan*/  max_pkt; } ;
struct socket {int type; struct proto_ops const* ops; } ;
struct sock {int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_backlog_rcv; scalar_t__ sk_shutdown; int /*<<< orphan*/  sk_timer; } ;
struct proto_ops {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_TIPC ; 
 int /*<<< orphan*/  CONN_TIMEOUT_DEFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTONOSUPPORT ; 
 int EPROTOTYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PKT_DEFAULT ; 
 int /*<<< orphan*/  NAMED_H_SIZE ; 
 int /*<<< orphan*/  RCVBUF_MIN ; 
#define  SOCK_DGRAM 131 
#define  SOCK_RDM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  TIPC_DUMP_NONE ; 
 int /*<<< orphan*/  TIPC_LOW_IMPORTANCE ; 
 int /*<<< orphan*/  TIPC_NAMED_MSG ; 
 int /*<<< orphan*/  TIPC_OPEN ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct proto_ops msg_ops ; 
 int /*<<< orphan*/  msg_set_origport (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 struct proto_ops packet_ops ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 struct proto_ops stream_ops ; 
 int /*<<< orphan*/ * sysctl_tipc_rmem ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_data_ready ; 
 int /*<<< orphan*/  tipc_msg_init (int /*<<< orphan*/ ,struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_own_addr (struct net*) ; 
 int /*<<< orphan*/  tipc_proto ; 
 int /*<<< orphan*/  tipc_set_sk_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct tipc_sock* tipc_sk (struct sock*) ; 
 int /*<<< orphan*/  tipc_sk_backlog_rcv ; 
 scalar_t__ tipc_sk_insert (struct tipc_sock*) ; 
 int /*<<< orphan*/  tipc_sk_timeout ; 
 scalar_t__ tipc_sk_type_connectionless (struct sock*) ; 
 int /*<<< orphan*/  tipc_sock_destruct ; 
 int /*<<< orphan*/  tipc_write_space ; 
 int /*<<< orphan*/  trace_tipc_sk_create (struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tsk_adv_blocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsk_set_unreliable (struct tipc_sock*,int) ; 
 int /*<<< orphan*/  tsk_set_unreturnable (struct tipc_sock*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tipc_sk_create(struct net *net, struct socket *sock,
			  int protocol, int kern)
{
	const struct proto_ops *ops;
	struct sock *sk;
	struct tipc_sock *tsk;
	struct tipc_msg *msg;

	/* Validate arguments */
	if (unlikely(protocol != 0))
		return -EPROTONOSUPPORT;

	switch (sock->type) {
	case SOCK_STREAM:
		ops = &stream_ops;
		break;
	case SOCK_SEQPACKET:
		ops = &packet_ops;
		break;
	case SOCK_DGRAM:
	case SOCK_RDM:
		ops = &msg_ops;
		break;
	default:
		return -EPROTOTYPE;
	}

	/* Allocate socket's protocol area */
	sk = sk_alloc(net, AF_TIPC, GFP_KERNEL, &tipc_proto, kern);
	if (sk == NULL)
		return -ENOMEM;

	tsk = tipc_sk(sk);
	tsk->max_pkt = MAX_PKT_DEFAULT;
	INIT_LIST_HEAD(&tsk->publications);
	INIT_LIST_HEAD(&tsk->cong_links);
	msg = &tsk->phdr;

	/* Finish initializing socket data structures */
	sock->ops = ops;
	sock_init_data(sock, sk);
	tipc_set_sk_state(sk, TIPC_OPEN);
	if (tipc_sk_insert(tsk)) {
		pr_warn("Socket create failed; port number exhausted\n");
		return -EINVAL;
	}

	/* Ensure tsk is visible before we read own_addr. */
	smp_mb();

	tipc_msg_init(tipc_own_addr(net), msg, TIPC_LOW_IMPORTANCE,
		      TIPC_NAMED_MSG, NAMED_H_SIZE, 0);

	msg_set_origport(msg, tsk->portid);
	timer_setup(&sk->sk_timer, tipc_sk_timeout, 0);
	sk->sk_shutdown = 0;
	sk->sk_backlog_rcv = tipc_sk_backlog_rcv;
	sk->sk_rcvbuf = sysctl_tipc_rmem[1];
	sk->sk_data_ready = tipc_data_ready;
	sk->sk_write_space = tipc_write_space;
	sk->sk_destruct = tipc_sock_destruct;
	tsk->conn_timeout = CONN_TIMEOUT_DEFAULT;
	tsk->group_is_open = true;
	atomic_set(&tsk->dupl_rcvcnt, 0);

	/* Start out with safe limits until we receive an advertised window */
	tsk->snd_win = tsk_adv_blocks(RCVBUF_MIN);
	tsk->rcv_win = tsk->snd_win;

	if (tipc_sk_type_connectionless(sk)) {
		tsk_set_unreturnable(tsk, true);
		if (sock->type == SOCK_DGRAM)
			tsk_set_unreliable(tsk, true);
	}
	__skb_queue_head_init(&tsk->mc_method.deferredq);
	trace_tipc_sk_create(sk, NULL, TIPC_DUMP_NONE, " ");
	return 0;
}