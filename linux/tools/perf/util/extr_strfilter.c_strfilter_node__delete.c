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
struct strfilter_node {struct strfilter_node* r; struct strfilter_node* l; int /*<<< orphan*/ * p; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct strfilter_node*) ; 
 int /*<<< orphan*/  is_operator (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (char**) ; 

__attribute__((used)) static void strfilter_node__delete(struct strfilter_node *node)
{
	if (node) {
		if (node->p && !is_operator(*node->p))
			zfree((char **)&node->p);
		strfilter_node__delete(node->l);
		strfilter_node__delete(node->r);
		free(node);
	}
}