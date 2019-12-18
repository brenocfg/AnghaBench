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
struct sparsebit {int dummy; } ;
struct node {int dummy; } ;
typedef  int /*<<< orphan*/  sparsebit_idx_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct node* node_first (struct sparsebit*) ; 
 int /*<<< orphan*/  node_first_set (struct node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_any_set (struct sparsebit*) ; 

sparsebit_idx_t sparsebit_first_set(struct sparsebit *s)
{
	struct node *nodep;

	/* Validate at least 1 bit is set */
	assert(sparsebit_any_set(s));

	nodep = node_first(s);
	return node_first_set(nodep, 0);
}