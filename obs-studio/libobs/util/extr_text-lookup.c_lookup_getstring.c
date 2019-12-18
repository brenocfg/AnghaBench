#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct text_node {TYPE_2__* leaf; TYPE_1__ str; } ;
struct TYPE_4__ {char* value; } ;

/* Variables and functions */
 struct text_node* text_node_byname (struct text_node*,char const*) ; 

__attribute__((used)) static inline bool lookup_getstring(const char *lookup_val, const char **out,
				    struct text_node *node)
{
	struct text_node *child;
	char ch;

	if (!node)
		return false;

	child = text_node_byname(node, lookup_val);
	if (!child)
		return false;

	lookup_val += child->str.len;
	ch = *lookup_val;
	if (ch)
		return lookup_getstring(lookup_val, out, child);

	if (!child->leaf)
		return false;

	*out = child->leaf->value;
	return true;
}