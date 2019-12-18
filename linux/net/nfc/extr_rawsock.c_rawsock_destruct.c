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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_receive_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  target_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFC_TARGET_MODE_IDLE ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ TCP_ESTABLISHED ; 
 int /*<<< orphan*/  nfc_deactivate_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfc_put_device (int /*<<< orphan*/ ) ; 
 TYPE_1__* nfc_rawsock (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,struct sock*) ; 
 int /*<<< orphan*/  pr_err (char*,struct sock*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rawsock_destruct(struct sock *sk)
{
	pr_debug("sk=%p\n", sk);

	if (sk->sk_state == TCP_ESTABLISHED) {
		nfc_deactivate_target(nfc_rawsock(sk)->dev,
				      nfc_rawsock(sk)->target_idx,
				      NFC_TARGET_MODE_IDLE);
		nfc_put_device(nfc_rawsock(sk)->dev);
	}

	skb_queue_purge(&sk->sk_receive_queue);

	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_err("Freeing alive NFC raw socket %p\n", sk);
		return;
	}
}