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
struct nameidata {int flags; int depth; int /*<<< orphan*/  root; TYPE_1__* stack; int /*<<< orphan*/  path; } ;
struct TYPE_2__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int LOOKUP_RCU ; 
 int LOOKUP_ROOT_GRABBED ; 
 int /*<<< orphan*/  drop_links (struct nameidata*) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void terminate_walk(struct nameidata *nd)
{
	drop_links(nd);
	if (!(nd->flags & LOOKUP_RCU)) {
		int i;
		path_put(&nd->path);
		for (i = 0; i < nd->depth; i++)
			path_put(&nd->stack[i].link);
		if (nd->flags & LOOKUP_ROOT_GRABBED) {
			path_put(&nd->root);
			nd->flags &= ~LOOKUP_ROOT_GRABBED;
		}
	} else {
		nd->flags &= ~LOOKUP_RCU;
		rcu_read_unlock();
	}
	nd->depth = 0;
}