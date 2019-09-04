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
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_fits_shwi_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline HOST_WIDE_INT tree_to_shwi(const_tree t)
{
	gcc_assert(tree_fits_shwi_p(t));
	return TREE_INT_CST_LOW(t);
}