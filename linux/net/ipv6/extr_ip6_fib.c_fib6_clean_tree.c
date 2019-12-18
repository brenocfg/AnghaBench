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
struct fib6_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ skip_in_node; scalar_t__ skip; scalar_t__ count; int /*<<< orphan*/  func; struct fib6_node* root; } ;
struct fib6_cleaner {int (* func ) (struct fib6_info*,void*) ;int sernum; int skip_notify; TYPE_1__ w; struct net* net; void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  fib6_clean_node ; 
 int /*<<< orphan*/  fib6_walk (struct net*,TYPE_1__*) ; 

__attribute__((used)) static void fib6_clean_tree(struct net *net, struct fib6_node *root,
			    int (*func)(struct fib6_info *, void *arg),
			    int sernum, void *arg, bool skip_notify)
{
	struct fib6_cleaner c;

	c.w.root = root;
	c.w.func = fib6_clean_node;
	c.w.count = 0;
	c.w.skip = 0;
	c.w.skip_in_node = 0;
	c.func = func;
	c.sernum = sernum;
	c.arg = arg;
	c.net = net;
	c.skip_notify = skip_notify;

	fib6_walk(net, &c.w);
}