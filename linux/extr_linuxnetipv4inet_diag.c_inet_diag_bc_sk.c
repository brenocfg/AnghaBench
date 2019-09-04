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
struct sock {scalar_t__ sk_state; scalar_t__ sk_mark; int /*<<< orphan*/  sk_userlocks; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_family; } ;
struct nlattr {int dummy; } ;
struct inet_sock {int /*<<< orphan*/  inet_dport; int /*<<< orphan*/  inet_num; } ;
struct inet_diag_entry {scalar_t__ mark; int /*<<< orphan*/  userlocks; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; int /*<<< orphan*/  family; } ;
struct TYPE_2__ {scalar_t__ ir_mark; } ;

/* Variables and functions */
 scalar_t__ TCP_NEW_SYN_RECV ; 
 int /*<<< orphan*/  entry_fill_addrs (struct inet_diag_entry*,struct sock*) ; 
 int inet_diag_bc_run (struct nlattr const*,struct inet_diag_entry*) ; 
 int /*<<< orphan*/  inet_reqsk (struct sock*) ; 
 TYPE_1__* inet_rsk (int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ sk_fullsock (struct sock*) ; 

int inet_diag_bc_sk(const struct nlattr *bc, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct inet_diag_entry entry;

	if (!bc)
		return 1;

	entry.family = sk->sk_family;
	entry_fill_addrs(&entry, sk);
	entry.sport = inet->inet_num;
	entry.dport = ntohs(inet->inet_dport);
	entry.ifindex = sk->sk_bound_dev_if;
	entry.userlocks = sk_fullsock(sk) ? sk->sk_userlocks : 0;
	if (sk_fullsock(sk))
		entry.mark = sk->sk_mark;
	else if (sk->sk_state == TCP_NEW_SYN_RECV)
		entry.mark = inet_rsk(inet_reqsk(sk))->ir_mark;
	else
		entry.mark = 0;

	return inet_diag_bc_run(bc, &entry);
}