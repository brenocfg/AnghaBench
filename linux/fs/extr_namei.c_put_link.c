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
struct saved {int /*<<< orphan*/  link; int /*<<< orphan*/  done; } ;
struct nameidata {int depth; int flags; struct saved* stack; } ;

/* Variables and functions */
 int LOOKUP_RCU ; 
 int /*<<< orphan*/  do_delayed_call (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void put_link(struct nameidata *nd)
{
	struct saved *last = nd->stack + --nd->depth;
	do_delayed_call(&last->done);
	if (!(nd->flags & LOOKUP_RCU))
		path_put(&last->link);
}