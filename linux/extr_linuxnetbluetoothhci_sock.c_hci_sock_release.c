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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_write_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  promisc; } ;
struct TYPE_2__ {int channel; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
#define  HCI_CHANNEL_CONTROL 131 
#define  HCI_CHANNEL_MONITOR 130 
#define  HCI_CHANNEL_RAW 129 
#define  HCI_CHANNEL_USER 128 
 int /*<<< orphan*/  HCI_SOCK_TRUSTED ; 
 int /*<<< orphan*/  HCI_USER_CHANNEL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_sock_unlink (int /*<<< orphan*/ *,struct sock*) ; 
 struct sk_buff* create_monitor_ctrl_close (struct sock*) ; 
 int /*<<< orphan*/  hci_dev_clear_flag (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_do_close (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 TYPE_1__* hci_pi (struct sock*) ; 
 int /*<<< orphan*/  hci_send_to_channel (int const,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_sk_list ; 
 int /*<<< orphan*/  hci_sock_free_cookie (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mgmt_index_added (struct hci_dev*) ; 
 int /*<<< orphan*/  monitor_promisc ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_orphan (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 

__attribute__((used)) static int hci_sock_release(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct hci_dev *hdev;
	struct sk_buff *skb;

	BT_DBG("sock %p sk %p", sock, sk);

	if (!sk)
		return 0;

	switch (hci_pi(sk)->channel) {
	case HCI_CHANNEL_MONITOR:
		atomic_dec(&monitor_promisc);
		break;
	case HCI_CHANNEL_RAW:
	case HCI_CHANNEL_USER:
	case HCI_CHANNEL_CONTROL:
		/* Send event to monitor */
		skb = create_monitor_ctrl_close(sk);
		if (skb) {
			hci_send_to_channel(HCI_CHANNEL_MONITOR, skb,
					    HCI_SOCK_TRUSTED, NULL);
			kfree_skb(skb);
		}

		hci_sock_free_cookie(sk);
		break;
	}

	bt_sock_unlink(&hci_sk_list, sk);

	hdev = hci_pi(sk)->hdev;
	if (hdev) {
		if (hci_pi(sk)->channel == HCI_CHANNEL_USER) {
			/* When releasing a user channel exclusive access,
			 * call hci_dev_do_close directly instead of calling
			 * hci_dev_close to ensure the exclusive access will
			 * be released and the controller brought back down.
			 *
			 * The checking of HCI_AUTO_OFF is not needed in this
			 * case since it will have been cleared already when
			 * opening the user channel.
			 */
			hci_dev_do_close(hdev);
			hci_dev_clear_flag(hdev, HCI_USER_CHANNEL);
			mgmt_index_added(hdev);
		}

		atomic_dec(&hdev->promisc);
		hci_dev_put(hdev);
	}

	sock_orphan(sk);

	skb_queue_purge(&sk->sk_receive_queue);
	skb_queue_purge(&sk->sk_write_queue);

	sock_put(sk);
	return 0;
}