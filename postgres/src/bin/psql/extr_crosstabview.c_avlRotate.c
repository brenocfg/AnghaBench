#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__** children; } ;
typedef  TYPE_1__ avl_node ;

/* Variables and functions */
 int /*<<< orphan*/  avlUpdateHeight (TYPE_1__*) ; 

__attribute__((used)) static avl_node *
avlRotate(avl_node **current, int dir)
{
	avl_node   *before = *current;
	avl_node   *after = (*current)->children[dir];

	*current = after;
	before->children[dir] = after->children[!dir];
	avlUpdateHeight(before);
	after->children[!dir] = before;

	return after;
}