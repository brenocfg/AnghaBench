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

/* Variables and functions */
 unsigned int EROFS_INODE_FLAT_COMPRESSION ; 
 unsigned int EROFS_INODE_FLAT_COMPRESSION_LEGACY ; 

__attribute__((used)) static inline bool erofs_inode_is_data_compressed(unsigned int datamode)
{
	return datamode == EROFS_INODE_FLAT_COMPRESSION ||
		datamode == EROFS_INODE_FLAT_COMPRESSION_LEGACY;
}