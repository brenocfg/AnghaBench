#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct sock {TYPE_1__ sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int tx_work_scheduled; int /*<<< orphan*/  tx_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_irq () ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 TYPE_2__* nfc_rawsock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*,int) ; 
 int rawsock_add_header (struct sk_buff*) ; 
 int /*<<< orphan*/  rawsock_report_error (struct sock*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rawsock_data_exchange_complete(void *context, struct sk_buff *skb,
					   int err)
{
	struct sock *sk = (struct sock *) context;

	BUG_ON(in_irq());

	pr_debug("sk=%p err=%d\n", sk, err);

	if (err)
		goto error;

	err = rawsock_add_header(skb);
	if (err)
		goto error_skb;

	err = sock_queue_rcv_skb(sk, skb);
	if (err)
		goto error_skb;

	spin_lock_bh(&sk->sk_write_queue.lock);
	if (!skb_queue_empty(&sk->sk_write_queue))
		schedule_work(&nfc_rawsock(sk)->tx_work);
	else
		nfc_rawsock(sk)->tx_work_scheduled = false;
	spin_unlock_bh(&sk->sk_write_queue.lock);

	sock_put(sk);
	return;

error_skb:
	kfree_skb(skb);

error:
	rawsock_report_error(sk, err);
	sock_put(sk);
}