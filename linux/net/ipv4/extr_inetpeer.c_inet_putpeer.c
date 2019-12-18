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
struct inet_peer {int /*<<< orphan*/  rcu; int /*<<< orphan*/  refcnt; scalar_t__ dtime; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inetpeer_free_rcu ; 
 scalar_t__ jiffies ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

void inet_putpeer(struct inet_peer *p)
{
	p->dtime = (__u32)jiffies;

	if (refcount_dec_and_test(&p->refcnt))
		call_rcu(&p->rcu, inetpeer_free_rcu);
}