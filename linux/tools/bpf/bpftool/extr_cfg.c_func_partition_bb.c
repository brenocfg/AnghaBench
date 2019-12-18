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
struct func_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ func_partition_bb_head (struct func_node*) ; 
 int /*<<< orphan*/  func_partition_bb_tail (struct func_node*) ; 

__attribute__((used)) static bool func_partition_bb(struct func_node *func)
{
	if (func_partition_bb_head(func))
		return true;

	func_partition_bb_tail(func);

	return false;
}