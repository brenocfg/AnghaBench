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
struct netlink_callback {scalar_t__* args; } ;
struct ila_dump_iter {int /*<<< orphan*/  rhiter; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ila_dump_iter*) ; 
 int /*<<< orphan*/  rhashtable_walk_exit (int /*<<< orphan*/ *) ; 

int ila_xlat_nl_dump_done(struct netlink_callback *cb)
{
	struct ila_dump_iter *iter = (struct ila_dump_iter *)cb->args[0];

	rhashtable_walk_exit(&iter->rhiter);

	kfree(iter);

	return 0;
}