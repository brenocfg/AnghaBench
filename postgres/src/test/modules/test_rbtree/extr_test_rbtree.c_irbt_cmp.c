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
struct TYPE_2__ {int key; } ;
typedef  int /*<<< orphan*/  RBTNode ;
typedef  TYPE_1__ IntRBTreeNode ;

/* Variables and functions */

__attribute__((used)) static int
irbt_cmp(const RBTNode *a, const RBTNode *b, void *arg)
{
	const IntRBTreeNode *ea = (const IntRBTreeNode *) a;
	const IntRBTreeNode *eb = (const IntRBTreeNode *) b;

	return ea->key - eb->key;
}