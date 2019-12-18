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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  RADIX_TREE_PRELOAD_SIZE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __radix_tree_preload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 

int radix_tree_preload(gfp_t gfp_mask)
{
	/* Warn on non-sensical use... */
	WARN_ON_ONCE(!gfpflags_allow_blocking(gfp_mask));
	return __radix_tree_preload(gfp_mask, RADIX_TREE_PRELOAD_SIZE);
}