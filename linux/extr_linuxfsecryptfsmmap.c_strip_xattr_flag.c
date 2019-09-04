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
struct ecryptfs_crypt_stat {int flags; } ;

/* Variables and functions */
 int ECRYPTFS_METADATA_IN_XATTR ; 
 int /*<<< orphan*/  ecryptfs_write_crypt_stat_flags (char*,struct ecryptfs_crypt_stat*,size_t*) ; 

__attribute__((used)) static void strip_xattr_flag(char *page_virt,
			     struct ecryptfs_crypt_stat *crypt_stat)
{
	if (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR) {
		size_t written;

		crypt_stat->flags &= ~ECRYPTFS_METADATA_IN_XATTR;
		ecryptfs_write_crypt_stat_flags(page_virt, crypt_stat,
						&written);
		crypt_stat->flags |= ECRYPTFS_METADATA_IN_XATTR;
	}
}