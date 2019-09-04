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
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
struct sock {int sk_shutdown; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int dummy; } ;
struct nfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  target_idx; struct nfc_dev* dev; } ;

/* Variables and functions */
 int SEND_SHUTDOWN ; 
 int nfc_data_exchange (struct nfc_dev*,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,struct sock*) ; 
 TYPE_1__* nfc_rawsock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawsock_data_exchange_complete ; 
 int /*<<< orphan*/  rawsock_report_error (struct sock*,int) ; 
 int /*<<< orphan*/  rawsock_write_queue_purge (struct sock*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 struct sock* to_rawsock_sk (struct work_struct*) ; 

__attribute__((used)) static void rawsock_tx_work(struct work_struct *work)
{
	struct sock *sk = to_rawsock_sk(work);
	struct nfc_dev *dev = nfc_rawsock(sk)->dev;
	u32 target_idx = nfc_rawsock(sk)->target_idx;
	struct sk_buff *skb;
	int rc;

	pr_debug("sk=%p target_idx=%u\n", sk, target_idx);

	if (sk->sk_shutdown & SEND_SHUTDOWN) {
		rawsock_write_queue_purge(sk);
		return;
	}

	skb = skb_dequeue(&sk->sk_write_queue);

	sock_hold(sk);
	rc = nfc_data_exchange(dev, target_idx, skb,
			       rawsock_data_exchange_complete, sk);
	if (rc) {
		rawsock_report_error(sk, rc);
		sock_put(sk);
	}
}