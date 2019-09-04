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
struct address_space {int dummy; } ;

/* Variables and functions */
 int invalidate_inode_pages2_range (struct address_space*,int /*<<< orphan*/ ,int) ; 

int invalidate_inode_pages2(struct address_space *mapping)
{
	return invalidate_inode_pages2_range(mapping, 0, -1);
}