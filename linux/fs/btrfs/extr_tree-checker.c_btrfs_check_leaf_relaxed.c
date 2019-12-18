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
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int check_leaf (struct extent_buffer*,int) ; 

int btrfs_check_leaf_relaxed(struct extent_buffer *leaf)
{
	return check_leaf(leaf, false);
}