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
struct sockaddr_sco {int /*<<< orphan*/  sco_bdaddr; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  src; int /*<<< orphan*/  dst; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_BLUETOOTH ; 
 int /*<<< orphan*/  BT_DBG (char*,struct socket*,struct sock*) ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* sco_pi (struct sock*) ; 

__attribute__((used)) static int sco_sock_getname(struct socket *sock, struct sockaddr *addr,
			    int peer)
{
	struct sockaddr_sco *sa = (struct sockaddr_sco *) addr;
	struct sock *sk = sock->sk;

	BT_DBG("sock %p, sk %p", sock, sk);

	addr->sa_family = AF_BLUETOOTH;

	if (peer)
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->dst);
	else
		bacpy(&sa->sco_bdaddr, &sco_pi(sk)->src);

	return sizeof(struct sockaddr_sco);
}