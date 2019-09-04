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
struct socket {struct sock* sk; } ;
struct sockaddr_l2 {int /*<<< orphan*/  l2_bdaddr_type; scalar_t__ l2_cid; int /*<<< orphan*/  l2_psm; int /*<<< orphan*/  l2_family; int /*<<< orphan*/  l2_bdaddr; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct rfcomm_session {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  imtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BDADDR_BREDR ; 
 int /*<<< orphan*/  BT_ERR (char*,int) ; 
 int /*<<< orphan*/  BT_LISTEN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  L2CAP_PSM_RFCOMM ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_listen (struct socket*,int) ; 
 int /*<<< orphan*/  l2cap_mtu ; 
 TYPE_2__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int rfcomm_l2sock_create (struct socket**) ; 
 struct rfcomm_session* rfcomm_session_add (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static int rfcomm_add_listener(bdaddr_t *ba)
{
	struct sockaddr_l2 addr;
	struct socket *sock;
	struct sock *sk;
	struct rfcomm_session *s;
	int    err = 0;

	/* Create socket */
	err = rfcomm_l2sock_create(&sock);
	if (err < 0) {
		BT_ERR("Create socket failed %d", err);
		return err;
	}

	/* Bind socket */
	bacpy(&addr.l2_bdaddr, ba);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = cpu_to_le16(L2CAP_PSM_RFCOMM);
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	err = kernel_bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (err < 0) {
		BT_ERR("Bind failed %d", err);
		goto failed;
	}

	/* Set L2CAP options */
	sk = sock->sk;
	lock_sock(sk);
	l2cap_pi(sk)->chan->imtu = l2cap_mtu;
	release_sock(sk);

	/* Start listening on the socket */
	err = kernel_listen(sock, 10);
	if (err) {
		BT_ERR("Listen failed %d", err);
		goto failed;
	}

	/* Add listening session */
	s = rfcomm_session_add(sock, BT_LISTEN);
	if (!s) {
		err = -ENOMEM;
		goto failed;
	}

	return 0;
failed:
	sock_release(sock);
	return err;
}