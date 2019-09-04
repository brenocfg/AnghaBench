#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/ * rightmost; int /*<<< orphan*/ * leftmost; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ index_tree ;

/* Variables and functions */

__attribute__((used)) static void
index_tree_init(index_tree *tree)
{
	tree->root = NULL;
	tree->leftmost = NULL;
	tree->rightmost = NULL;
	tree->count = 0;
	return;
}