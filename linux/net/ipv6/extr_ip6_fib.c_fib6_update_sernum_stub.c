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
struct net {int dummy; } ;
struct fib6_info {TYPE_1__* fib6_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  tb6_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_update_sernum_upto_root (struct net*,struct fib6_info*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void fib6_update_sernum_stub(struct net *net, struct fib6_info *f6i)
{
	spin_lock_bh(&f6i->fib6_table->tb6_lock);
	fib6_update_sernum_upto_root(net, f6i);
	spin_unlock_bh(&f6i->fib6_table->tb6_lock);
}