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
struct TYPE_2__ {scalar_t__ key; } ;
typedef  int /*<<< orphan*/  RBTNode ;
typedef  TYPE_1__ IntRBTreeNode ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
irbt_combine(RBTNode *existing, const RBTNode *newdata, void *arg)
{
	const IntRBTreeNode *eexist = (const IntRBTreeNode *) existing;
	const IntRBTreeNode *enew = (const IntRBTreeNode *) newdata;

	if (eexist->key != enew->key)
		elog(ERROR, "red-black tree combines %d into %d",
			 enew->key, eexist->key);
}