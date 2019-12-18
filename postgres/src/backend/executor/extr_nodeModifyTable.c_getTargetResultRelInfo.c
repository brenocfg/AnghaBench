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
struct TYPE_3__ {int /*<<< orphan*/ * resultRelInfo; int /*<<< orphan*/ * rootResultRelInfo; } ;
typedef  int /*<<< orphan*/  ResultRelInfo ;
typedef  TYPE_1__ ModifyTableState ;

/* Variables and functions */

__attribute__((used)) static ResultRelInfo *
getTargetResultRelInfo(ModifyTableState *node)
{
	/*
	 * Note that if the node modifies a partitioned table, node->resultRelInfo
	 * points to the first leaf partition, not the root table.
	 */
	if (node->rootResultRelInfo != NULL)
		return node->rootResultRelInfo;
	else
		return node->resultRelInfo;
}