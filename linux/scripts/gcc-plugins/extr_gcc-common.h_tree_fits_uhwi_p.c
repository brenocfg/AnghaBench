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

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_HIGH (scalar_t__) ; 

__attribute__((used)) static inline bool tree_fits_uhwi_p(const_tree t)
{
	if (t == NULL_TREE || TREE_CODE(t) != INTEGER_CST)
		return false;

	return TREE_INT_CST_HIGH(t) == 0;
}