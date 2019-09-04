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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ sk_kern_sock; } ;
struct rxrpc_sock {TYPE_1__ sk; } ;
struct rxrpc_net {int /*<<< orphan*/  nr_calls; } ;
struct rxrpc_call {unsigned int debug_id; int tx_total_len; int next_rx_timo; int next_req_timo; int tx_winsize; int rx_expect_next; int cong_cwnd; void* rxtx_buffer; struct rxrpc_net* rxnet; scalar_t__ cong_ssthresh; int /*<<< orphan*/  rx_winsize; int /*<<< orphan*/  sock_node; int /*<<< orphan*/  usage; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  input_lock; int /*<<< orphan*/  notify_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; int /*<<< orphan*/  sock_link; int /*<<< orphan*/  recvmsg_link; int /*<<< orphan*/  accept_link; int /*<<< orphan*/  chan_wait_link; int /*<<< orphan*/  link; int /*<<< orphan*/  processor; int /*<<< orphan*/  timer; int /*<<< orphan*/  user_mutex; void* rxtx_annotations; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RXRPC_RXTX_BUFF_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rxrpc_call*) ; 
 struct rxrpc_call* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxrpc_call_jar ; 
 int /*<<< orphan*/  rxrpc_call_timer_expired ; 
 int /*<<< orphan*/  rxrpc_call_user_mutex_lock_class_key ; 
 struct rxrpc_net* rxrpc_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxrpc_process_call ; 
 int /*<<< orphan*/  rxrpc_rx_window_size ; 
 int /*<<< orphan*/  sock_net (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rxrpc_call *rxrpc_alloc_call(struct rxrpc_sock *rx, gfp_t gfp,
				    unsigned int debug_id)
{
	struct rxrpc_call *call;
	struct rxrpc_net *rxnet = rxrpc_net(sock_net(&rx->sk));

	call = kmem_cache_zalloc(rxrpc_call_jar, gfp);
	if (!call)
		return NULL;

	call->rxtx_buffer = kcalloc(RXRPC_RXTX_BUFF_SIZE,
				    sizeof(struct sk_buff *),
				    gfp);
	if (!call->rxtx_buffer)
		goto nomem;

	call->rxtx_annotations = kcalloc(RXRPC_RXTX_BUFF_SIZE, sizeof(u8), gfp);
	if (!call->rxtx_annotations)
		goto nomem_2;

	mutex_init(&call->user_mutex);

	/* Prevent lockdep reporting a deadlock false positive between the afs
	 * filesystem and sys_sendmsg() via the mmap sem.
	 */
	if (rx->sk.sk_kern_sock)
		lockdep_set_class(&call->user_mutex,
				  &rxrpc_call_user_mutex_lock_class_key);

	timer_setup(&call->timer, rxrpc_call_timer_expired, 0);
	INIT_WORK(&call->processor, &rxrpc_process_call);
	INIT_LIST_HEAD(&call->link);
	INIT_LIST_HEAD(&call->chan_wait_link);
	INIT_LIST_HEAD(&call->accept_link);
	INIT_LIST_HEAD(&call->recvmsg_link);
	INIT_LIST_HEAD(&call->sock_link);
	init_waitqueue_head(&call->waitq);
	spin_lock_init(&call->lock);
	spin_lock_init(&call->notify_lock);
	spin_lock_init(&call->input_lock);
	rwlock_init(&call->state_lock);
	atomic_set(&call->usage, 1);
	call->debug_id = debug_id;
	call->tx_total_len = -1;
	call->next_rx_timo = 20 * HZ;
	call->next_req_timo = 1 * HZ;

	memset(&call->sock_node, 0xed, sizeof(call->sock_node));

	/* Leave space in the ring to handle a maxed-out jumbo packet */
	call->rx_winsize = rxrpc_rx_window_size;
	call->tx_winsize = 16;
	call->rx_expect_next = 1;

	call->cong_cwnd = 2;
	call->cong_ssthresh = RXRPC_RXTX_BUFF_SIZE - 1;

	call->rxnet = rxnet;
	atomic_inc(&rxnet->nr_calls);
	return call;

nomem_2:
	kfree(call->rxtx_buffer);
nomem:
	kmem_cache_free(rxrpc_call_jar, call);
	return NULL;
}