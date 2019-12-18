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
struct socket {struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_state_change; int /*<<< orphan*/  sk_data_ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTPROTO_L2CAP ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  PF_BLUETOOTH ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  rfcomm_l2data_ready ; 
 int /*<<< orphan*/  rfcomm_l2state_change ; 
 int sock_create_kern (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 

__attribute__((used)) static int rfcomm_l2sock_create(struct socket **sock)
{
	int err;

	BT_DBG("");

	err = sock_create_kern(&init_net, PF_BLUETOOTH, SOCK_SEQPACKET, BTPROTO_L2CAP, sock);
	if (!err) {
		struct sock *sk = (*sock)->sk;
		sk->sk_data_ready   = rfcomm_l2data_ready;
		sk->sk_state_change = rfcomm_l2state_change;
	}
	return err;
}