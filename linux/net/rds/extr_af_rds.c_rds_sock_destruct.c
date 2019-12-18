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
struct TYPE_2__ {struct TYPE_2__* prev; struct TYPE_2__* next; } ;
struct rds_sock {TYPE_1__ rs_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct rds_sock* rds_sk_to_rs (struct sock*) ; 

__attribute__((used)) static void rds_sock_destruct(struct sock *sk)
{
	struct rds_sock *rs = rds_sk_to_rs(sk);

	WARN_ON((&rs->rs_item != rs->rs_item.next ||
		 &rs->rs_item != rs->rs_item.prev));
}