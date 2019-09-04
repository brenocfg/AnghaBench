#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {struct sock* sk; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {scalar_t__ a_addr; void* a_len; } ;
struct TYPE_6__ {TYPE_2__ sdn_add; void* sdn_objnamel; int /*<<< orphan*/  sdn_objname; scalar_t__ sdn_objnum; scalar_t__ sdn_flags; } ;
struct TYPE_4__ {int acc_accl; int /*<<< orphan*/  acc_acc; } ;
struct dn_scp {TYPE_3__ addr; TYPE_1__ accessdata; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  SOCK_ZAPPED ; 
 void* cpu_to_le16 (int) ; 
 int dn_dev_bind_default (int /*<<< orphan*/ *) ; 
 int dn_hash_sock (struct sock*) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sock_reset_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_set_flag (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dn_auto_bind(struct socket *sock)
{
	struct sock *sk = sock->sk;
	struct dn_scp *scp = DN_SK(sk);
	int rv;

	sock_reset_flag(sk, SOCK_ZAPPED);

	scp->addr.sdn_flags  = 0;
	scp->addr.sdn_objnum = 0;

	/*
	 * This stuff is to keep compatibility with Eduardo's
	 * patch. I hope I can dispense with it shortly...
	 */
	if ((scp->accessdata.acc_accl != 0) &&
		(scp->accessdata.acc_accl <= 12)) {

		scp->addr.sdn_objnamel = cpu_to_le16(scp->accessdata.acc_accl);
		memcpy(scp->addr.sdn_objname, scp->accessdata.acc_acc, le16_to_cpu(scp->addr.sdn_objnamel));

		scp->accessdata.acc_accl = 0;
		memset(scp->accessdata.acc_acc, 0, 40);
	}
	/* End of compatibility stuff */

	scp->addr.sdn_add.a_len = cpu_to_le16(2);
	rv = dn_dev_bind_default((__le16 *)scp->addr.sdn_add.a_addr);
	if (rv == 0) {
		rv = dn_hash_sock(sk);
		if (rv)
			sock_set_flag(sk, SOCK_ZAPPED);
	}

	return rv;
}