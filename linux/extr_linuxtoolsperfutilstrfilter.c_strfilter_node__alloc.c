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
struct strfilter_node {char const* p; struct strfilter_node* r; struct strfilter_node* l; } ;

/* Variables and functions */
 struct strfilter_node* zalloc (int) ; 

__attribute__((used)) static struct strfilter_node *strfilter_node__alloc(const char *op,
						    struct strfilter_node *l,
						    struct strfilter_node *r)
{
	struct strfilter_node *node = zalloc(sizeof(*node));

	if (node) {
		node->p = op;
		node->l = l;
		node->r = r;
	}

	return node;
}