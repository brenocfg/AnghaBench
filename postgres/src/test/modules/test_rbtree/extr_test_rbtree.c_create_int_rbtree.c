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
typedef  int /*<<< orphan*/  RBTree ;
typedef  int /*<<< orphan*/  IntRBTreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  irbt_alloc ; 
 int /*<<< orphan*/  irbt_cmp ; 
 int /*<<< orphan*/  irbt_combine ; 
 int /*<<< orphan*/  irbt_free ; 
 int /*<<< orphan*/ * rbt_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static RBTree *
create_int_rbtree(void)
{
	return rbt_create(sizeof(IntRBTreeNode),
					  irbt_cmp,
					  irbt_combine,
					  irbt_alloc,
					  irbt_free,
					  NULL);
}