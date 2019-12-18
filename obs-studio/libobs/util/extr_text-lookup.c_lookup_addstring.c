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
struct TYPE_2__ {size_t len; char* array; } ;
struct text_node {TYPE_1__ str; } ;
struct text_leaf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lookup_createsubnode (char const*,struct text_leaf*,struct text_node*) ; 
 int /*<<< orphan*/  lookup_replaceleaf (struct text_node*,struct text_leaf*) ; 
 int /*<<< orphan*/  lookup_splitnode (char const*,size_t,struct text_leaf*,struct text_node*) ; 
 struct text_node* text_node_bychar (struct text_node*,char const) ; 

__attribute__((used)) static void lookup_addstring(const char *lookup_val, struct text_leaf *leaf,
			     struct text_node *node)
{
	struct text_node *child;

	/* value already exists, so replace */
	if (!lookup_val || !*lookup_val) {
		lookup_replaceleaf(node, leaf);
		return;
	}

	child = text_node_bychar(node, *lookup_val);
	if (child) {
		size_t len;

		for (len = 0; len < child->str.len; len++) {
			char val1 = child->str.array[len],
			     val2 = lookup_val[len];

			if (val1 >= 'A' && val1 <= 'Z')
				val1 += 0x20;
			if (val2 >= 'A' && val2 <= 'Z')
				val2 += 0x20;

			if (val1 != val2)
				break;
		}

		if (len == child->str.len) {
			lookup_addstring(lookup_val + len, leaf, child);
			return;
		} else {
			lookup_splitnode(lookup_val, len, leaf, child);
		}
	} else {
		lookup_createsubnode(lookup_val, leaf, node);
	}
}