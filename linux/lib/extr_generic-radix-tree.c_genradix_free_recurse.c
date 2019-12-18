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
struct genradix_node {struct genradix_node** children; } ;

/* Variables and functions */
 unsigned int GENRADIX_ARY ; 
 int /*<<< orphan*/  genradix_free_node (struct genradix_node*) ; 

__attribute__((used)) static void genradix_free_recurse(struct genradix_node *n, unsigned level)
{
	if (level) {
		unsigned i;

		for (i = 0; i < GENRADIX_ARY; i++)
			if (n->children[i])
				genradix_free_recurse(n->children[i], level - 1);
	}

	genradix_free_node(n);
}