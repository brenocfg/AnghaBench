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
struct TYPE_2__ {struct rb_node* rb_left; struct rb_node* rb_right; } ;
struct ovl_cache_entry {int len; TYPE_1__ node; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ovl_cache_entry* ovl_cache_entry_from_node (struct rb_node*) ; 
 int strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool ovl_cache_entry_find_link(const char *name, int len,
				      struct rb_node ***link,
				      struct rb_node **parent)
{
	bool found = false;
	struct rb_node **newp = *link;

	while (!found && *newp) {
		int cmp;
		struct ovl_cache_entry *tmp;

		*parent = *newp;
		tmp = ovl_cache_entry_from_node(*newp);
		cmp = strncmp(name, tmp->name, len);
		if (cmp > 0)
			newp = &tmp->node.rb_right;
		else if (cmp < 0 || len < tmp->len)
			newp = &tmp->node.rb_left;
		else
			found = true;
	}
	*link = newp;

	return found;
}