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
typedef  int /*<<< orphan*/  const_tree ;

/* Variables and functions */
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_fptr(const_tree fieldtype)
{
	if (TREE_CODE(fieldtype) != POINTER_TYPE)
		return false;

	return TREE_CODE(TREE_TYPE(fieldtype)) == FUNCTION_TYPE;
}