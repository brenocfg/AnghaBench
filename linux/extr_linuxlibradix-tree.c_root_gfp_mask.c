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
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_ZONEMASK ; 
 int __GFP_BITS_MASK ; 

__attribute__((used)) static inline gfp_t root_gfp_mask(const struct radix_tree_root *root)
{
	return root->gfp_mask & (__GFP_BITS_MASK & ~GFP_ZONEMASK);
}