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
typedef  scalar_t__ const_tree ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int TREE_INT_CST_HIGH (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool tree_fits_shwi_p(const_tree t)
{
	if (t == NULL_TREE || TREE_CODE(t) != INTEGER_CST)
		return false;

	if (TREE_INT_CST_HIGH(t) == 0 && (HOST_WIDE_INT)TREE_INT_CST_LOW(t) >= 0)
		return true;

	if (TREE_INT_CST_HIGH(t) == -1 && (HOST_WIDE_INT)TREE_INT_CST_LOW(t) < 0 && !TYPE_UNSIGNED(TREE_TYPE(t)))
		return true;

	return false;
}