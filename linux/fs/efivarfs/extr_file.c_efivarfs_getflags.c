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
struct inode {unsigned int i_flags; } ;

/* Variables and functions */
 unsigned int FS_IMMUTABLE_FL ; 
 unsigned int S_IMMUTABLE ; 

__attribute__((used)) static inline unsigned int efivarfs_getflags(struct inode *inode)
{
	unsigned int i_flags;
	unsigned int flags = 0;

	i_flags = inode->i_flags;
	if (i_flags & S_IMMUTABLE)
		flags |= FS_IMMUTABLE_FL;
	return flags;
}