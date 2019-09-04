#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct ecryptfs_crypt_stat {int flags; scalar_t__ file_version; } ;
struct TYPE_3__ {int local_flag; int file_flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* ecryptfs_flag_map ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,char*) ; 

void ecryptfs_write_crypt_stat_flags(char *page_virt,
				     struct ecryptfs_crypt_stat *crypt_stat,
				     size_t *written)
{
	u32 flags = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(ecryptfs_flag_map); i++)
		if (crypt_stat->flags & ecryptfs_flag_map[i].local_flag)
			flags |= ecryptfs_flag_map[i].file_flag;
	/* Version is in top 8 bits of the 32-bit flag vector */
	flags |= ((((u8)crypt_stat->file_version) << 24) & 0xFF000000);
	put_unaligned_be32(flags, page_virt);
	(*written) = 4;
}