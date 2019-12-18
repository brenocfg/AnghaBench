#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sockaddr {int dummy; } ;
struct sockaddr_llc {int /*<<< orphan*/  sllc_family; struct sockaddr sllc_mac; int /*<<< orphan*/  sllc_arphrd; int /*<<< orphan*/  sllc_sap; } ;
struct sock {scalar_t__ sk_state; } ;
struct TYPE_5__ {struct sockaddr_llc mac; int /*<<< orphan*/  lsap; } ;
struct llc_sock {TYPE_4__* dev; TYPE_3__* sap; TYPE_1__ daddr; } ;
typedef  int /*<<< orphan*/  sllc ;
struct TYPE_8__ {struct sockaddr_llc* dev_addr; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  lsap; } ;
struct TYPE_7__ {TYPE_2__ laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LLC ; 
 int EBADF ; 
 int EINVAL ; 
 int ENOTCONN ; 
 int IFHWADDRLEN ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 scalar_t__ TCP_ESTABLISHED ; 
 struct llc_sock* llc_sk (struct sock*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,struct sockaddr_llc*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_llc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int llc_ui_getname(struct socket *sock, struct sockaddr *uaddr,
			  int peer)
{
	struct sockaddr_llc sllc;
	struct sock *sk = sock->sk;
	struct llc_sock *llc = llc_sk(sk);
	int rc = -EBADF;

	memset(&sllc, 0, sizeof(sllc));
	lock_sock(sk);
	if (sock_flag(sk, SOCK_ZAPPED))
		goto out;
	if (peer) {
		rc = -ENOTCONN;
		if (sk->sk_state != TCP_ESTABLISHED)
			goto out;
		if(llc->dev)
			sllc.sllc_arphrd = llc->dev->type;
		sllc.sllc_sap = llc->daddr.lsap;
		memcpy(&sllc.sllc_mac, &llc->daddr.mac, IFHWADDRLEN);
	} else {
		rc = -EINVAL;
		if (!llc->sap)
			goto out;
		sllc.sllc_sap = llc->sap->laddr.lsap;

		if (llc->dev) {
			sllc.sllc_arphrd = llc->dev->type;
			memcpy(&sllc.sllc_mac, llc->dev->dev_addr,
			       IFHWADDRLEN);
		}
	}
	sllc.sllc_family = AF_LLC;
	memcpy(uaddr, &sllc, sizeof(sllc));
	rc = sizeof(sllc);
out:
	release_sock(sk);
	return rc;
}