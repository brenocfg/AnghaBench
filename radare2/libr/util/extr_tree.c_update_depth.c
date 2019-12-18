#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* parent; scalar_t__ depth; } ;
struct TYPE_4__ {scalar_t__ depth; } ;
typedef  int /*<<< orphan*/  RTreeVisitor ;
typedef  TYPE_2__ RTreeNode ;

/* Variables and functions */

__attribute__((used)) static void update_depth (RTreeNode *n, RTreeVisitor *vis) {
	n->depth = n->parent ? n->parent->depth + 1 : 0;
}