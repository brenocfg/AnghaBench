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
struct ubifs_orphan {int /*<<< orphan*/  new_list; scalar_t__ new; int /*<<< orphan*/  list; int /*<<< orphan*/  rb; } ;
struct ubifs_info {int tot_orphans; int new_orphans; int /*<<< orphan*/  orph_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ubifs_orphan*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __orphan_drop(struct ubifs_info *c, struct ubifs_orphan *o)
{
	rb_erase(&o->rb, &c->orph_tree);
	list_del(&o->list);
	c->tot_orphans -= 1;

	if (o->new) {
		list_del(&o->new_list);
		c->new_orphans -= 1;
	}

	kfree(o);
}