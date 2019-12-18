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
typedef  int /*<<< orphan*/  uid_t ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIX_DIAG_UID ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_i_uid (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump_uid(struct sock *sk, struct sk_buff *nlskb)
{
	uid_t uid = from_kuid_munged(sk_user_ns(nlskb->sk), sock_i_uid(sk));
	return nla_put(nlskb, UNIX_DIAG_UID, sizeof(uid_t), &uid);
}