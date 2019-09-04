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
struct TYPE_2__ {scalar_t__ overflow; } ;
struct befs_btree_node {TYPE_1__ head; } ;

/* Variables and functions */
 scalar_t__ BEFS_BT_INVAL ; 

__attribute__((used)) static int
befs_leafnode(struct befs_btree_node *node)
{
	/* all interior nodes (and only interior nodes) have an overflow node */
	if (node->head.overflow == BEFS_BT_INVAL)
		return 1;
	else
		return 0;
}