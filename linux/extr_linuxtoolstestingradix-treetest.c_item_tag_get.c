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
struct radix_tree_root {int dummy; } ;

/* Variables and functions */
 int radix_tree_tag_get (struct radix_tree_root*,unsigned long,int) ; 

int item_tag_get(struct radix_tree_root *root, unsigned long index, int tag)
{
	return radix_tree_tag_get(root, index, tag);
}