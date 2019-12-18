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
struct rhashtable_iter {int dummy; } ;
struct netlink_callback {int* args; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rhashtable_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (struct rhashtable_iter*) ; 

__attribute__((used)) static int netlink_diag_dump_done(struct netlink_callback *cb)
{
	struct rhashtable_iter *hti = (void *)cb->args[2];

	if (cb->args[0] == 1)
		rhashtable_walk_exit(hti);

	kfree(hti);

	return 0;
}