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
struct sparsebit {struct node* root; } ;
struct node {struct node* left; } ;

/* Variables and functions */

__attribute__((used)) static struct node *node_first(struct sparsebit *s)
{
	struct node *nodep;

	for (nodep = s->root; nodep && nodep->left; nodep = nodep->left)
		;

	return nodep;
}