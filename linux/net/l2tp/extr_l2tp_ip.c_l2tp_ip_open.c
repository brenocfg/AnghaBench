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
struct sock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_L2TP ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  l2tp_ip_lock ; 
 int /*<<< orphan*/  l2tp_ip_table ; 
 int /*<<< orphan*/  sk_add_node (struct sock*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int l2tp_ip_open(struct sock *sk)
{
	/* Prevent autobind. We don't have ports. */
	inet_sk(sk)->inet_num = IPPROTO_L2TP;

	write_lock_bh(&l2tp_ip_lock);
	sk_add_node(sk, &l2tp_ip_table);
	write_unlock_bh(&l2tp_ip_lock);

	return 0;
}