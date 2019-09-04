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
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  truncate_inode_pages_range (struct address_space*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void truncate_inode_pages(struct address_space *mapping, loff_t lstart)
{
	truncate_inode_pages_range(mapping, lstart, (loff_t)-1);
}