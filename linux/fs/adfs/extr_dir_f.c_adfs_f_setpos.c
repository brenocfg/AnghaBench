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
struct adfs_dir {int pos; } ;

/* Variables and functions */
 unsigned int ADFS_NUM_DIR_ENTRIES ; 
 int ENOENT ; 

__attribute__((used)) static int
adfs_f_setpos(struct adfs_dir *dir, unsigned int fpos)
{
	if (fpos >= ADFS_NUM_DIR_ENTRIES)
		return -ENOENT;

	dir->pos = 5 + fpos * 26;
	return 0;
}