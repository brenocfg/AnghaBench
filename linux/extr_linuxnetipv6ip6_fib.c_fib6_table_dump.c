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
struct net {int dummy; } ;
struct fib6_walker {int /*<<< orphan*/ * root; } ;
struct fib6_table {int /*<<< orphan*/  tb6_lock; int /*<<< orphan*/  tb6_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_walk (struct net*,struct fib6_walker*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fib6_table_dump(struct net *net, struct fib6_table *tb,
			    struct fib6_walker *w)
{
	w->root = &tb->tb6_root;
	spin_lock_bh(&tb->tb6_lock);
	fib6_walk(net, w);
	spin_unlock_bh(&tb->tb6_lock);
}