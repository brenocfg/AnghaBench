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
struct radix_tree_root {int gfp_mask; } ;

/* Variables and functions */
 int ROOT_TAG_SHIFT ; 

__attribute__((used)) static inline void root_tag_clear_all(struct radix_tree_root *root)
{
	root->gfp_mask &= (1 << ROOT_TAG_SHIFT) - 1;
}