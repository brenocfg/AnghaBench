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
struct inode {int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  configfs_file_operations ; 

__attribute__((used)) static void configfs_init_file(struct inode * inode)
{
	inode->i_size = PAGE_SIZE;
	inode->i_fop = &configfs_file_operations;
}