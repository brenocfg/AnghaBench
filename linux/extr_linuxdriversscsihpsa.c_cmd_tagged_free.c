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
struct ctlr_info {int dummy; } ;
struct CommandList {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cmd_tagged_free(struct ctlr_info *h, struct CommandList *c)
{
	/*
	 * Release our reference to the block.  We don't need to do anything
	 * else to free it, because it is accessed by index.
	 */
	(void)atomic_dec(&c->refcount);
}