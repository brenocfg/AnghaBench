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
 unsigned long NFS_DEF_FILE_IO_SIZE ; 
 unsigned long NFS_MAX_FILE_IO_SIZE ; 
 unsigned long NFS_MIN_FILE_IO_SIZE ; 
 unsigned long nfs_block_bits (unsigned long,unsigned char*) ; 

__attribute__((used)) static inline
unsigned long nfs_block_size(unsigned long bsize, unsigned char *nrbitsp)
{
	if (bsize < NFS_MIN_FILE_IO_SIZE)
		bsize = NFS_DEF_FILE_IO_SIZE;
	else if (bsize >= NFS_MAX_FILE_IO_SIZE)
		bsize = NFS_MAX_FILE_IO_SIZE;

	return nfs_block_bits(bsize, nrbitsp);
}