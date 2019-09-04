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
struct inode {scalar_t__ i_size; } ;

/* Variables and functions */
 scalar_t__ EMPTY_DIR_SIZE ; 
 scalar_t__ EMPTY_DIR_SIZE_V1 ; 

__attribute__((used)) static inline int reiserfs_empty_dir(struct inode *inode)
{
	/*
	 * we can cheat because an old format dir cannot have
	 * EMPTY_DIR_SIZE, and a new format dir cannot have
	 * EMPTY_DIR_SIZE_V1.  So, if the inode is either size,
	 * regardless of disk format version, the directory is empty.
	 */
	if (inode->i_size != EMPTY_DIR_SIZE &&
	    inode->i_size != EMPTY_DIR_SIZE_V1) {
		return 0;
	}
	return 1;
}