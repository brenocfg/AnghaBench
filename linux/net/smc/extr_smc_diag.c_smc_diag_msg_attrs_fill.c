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
struct user_namespace {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_shutdown; } ;
struct smc_diag_msg {int /*<<< orphan*/  diag_inode; int /*<<< orphan*/  diag_uid; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_DIAG_SHUTDOWN ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_i_ino (struct sock*) ; 
 int /*<<< orphan*/  sock_i_uid (struct sock*) ; 

__attribute__((used)) static int smc_diag_msg_attrs_fill(struct sock *sk, struct sk_buff *skb,
				   struct smc_diag_msg *r,
				   struct user_namespace *user_ns)
{
	if (nla_put_u8(skb, SMC_DIAG_SHUTDOWN, sk->sk_shutdown))
		return 1;

	r->diag_uid = from_kuid_munged(user_ns, sock_i_uid(sk));
	r->diag_inode = sock_i_ino(sk);
	return 0;
}