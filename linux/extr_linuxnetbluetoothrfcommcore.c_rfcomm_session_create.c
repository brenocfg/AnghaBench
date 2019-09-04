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
typedef  int /*<<< orphan*/  u8 ;
struct socket {struct sock* sk; } ;
struct sockaddr_l2 {void* l2_bdaddr_type; scalar_t__ l2_cid; scalar_t__ l2_psm; void* l2_family; int /*<<< orphan*/  l2_bdaddr; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct rfcomm_session {int initiator; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_4__ {TYPE_1__* chan; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  sec_level; int /*<<< orphan*/  imtu; } ;

/* Variables and functions */
 void* AF_BLUETOOTH ; 
 void* BDADDR_BREDR ; 
 int /*<<< orphan*/  BT_BOUND ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EINPROGRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  L2CAP_MODE_ERTM ; 
 int /*<<< orphan*/  L2CAP_PSM_RFCOMM ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_connect (struct socket*,struct sockaddr*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ l2cap_ertm ; 
 int /*<<< orphan*/  l2cap_mtu ; 
 TYPE_2__* l2cap_pi (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 int rfcomm_l2sock_create (struct socket**) ; 
 struct rfcomm_session* rfcomm_session_add (struct socket*,int /*<<< orphan*/ ) ; 
 struct rfcomm_session* rfcomm_session_del (struct rfcomm_session*) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

__attribute__((used)) static struct rfcomm_session *rfcomm_session_create(bdaddr_t *src,
							bdaddr_t *dst,
							u8 sec_level,
							int *err)
{
	struct rfcomm_session *s = NULL;
	struct sockaddr_l2 addr;
	struct socket *sock;
	struct sock *sk;

	BT_DBG("%pMR -> %pMR", src, dst);

	*err = rfcomm_l2sock_create(&sock);
	if (*err < 0)
		return NULL;

	bacpy(&addr.l2_bdaddr, src);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = 0;
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	*err = kernel_bind(sock, (struct sockaddr *) &addr, sizeof(addr));
	if (*err < 0)
		goto failed;

	/* Set L2CAP options */
	sk = sock->sk;
	lock_sock(sk);
	l2cap_pi(sk)->chan->imtu = l2cap_mtu;
	l2cap_pi(sk)->chan->sec_level = sec_level;
	if (l2cap_ertm)
		l2cap_pi(sk)->chan->mode = L2CAP_MODE_ERTM;
	release_sock(sk);

	s = rfcomm_session_add(sock, BT_BOUND);
	if (!s) {
		*err = -ENOMEM;
		goto failed;
	}

	s->initiator = 1;

	bacpy(&addr.l2_bdaddr, dst);
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm    = cpu_to_le16(L2CAP_PSM_RFCOMM);
	addr.l2_cid    = 0;
	addr.l2_bdaddr_type = BDADDR_BREDR;
	*err = kernel_connect(sock, (struct sockaddr *) &addr, sizeof(addr), O_NONBLOCK);
	if (*err == 0 || *err == -EINPROGRESS)
		return s;

	return rfcomm_session_del(s);

failed:
	sock_release(sock);
	return NULL;
}