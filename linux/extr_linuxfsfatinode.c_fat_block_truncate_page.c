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
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int block_truncate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fat_get_block ; 

int fat_block_truncate_page(struct inode *inode, loff_t from)
{
	return block_truncate_page(inode->i_mapping, from, fat_get_block);
}