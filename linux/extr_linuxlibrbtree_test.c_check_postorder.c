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
struct rb_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rb_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct rb_node* rb_first_postorder (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next_postorder (struct rb_node*) ; 
 TYPE_1__ root ; 

__attribute__((used)) static void check_postorder(int nr_nodes)
{
	struct rb_node *rb;
	int count = 0;
	for (rb = rb_first_postorder(&root.rb_root); rb; rb = rb_next_postorder(rb))
		count++;

	WARN_ON_ONCE(count != nr_nodes);
}