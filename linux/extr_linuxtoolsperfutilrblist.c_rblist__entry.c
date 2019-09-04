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
struct rblist {int /*<<< orphan*/  entries; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (struct rb_node*) ; 

struct rb_node *rblist__entry(const struct rblist *rblist, unsigned int idx)
{
	struct rb_node *node;

	for (node = rb_first(&rblist->entries); node; node = rb_next(node)) {
		if (!idx--)
			return node;
	}

	return NULL;
}