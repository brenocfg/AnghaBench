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
struct hfsc_class {TYPE_1__* cl_parent; int /*<<< orphan*/  cf_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  cf_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
cftree_remove(struct hfsc_class *cl)
{
	rb_erase(&cl->cf_node, &cl->cl_parent->cf_tree);
}