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
struct ecryptfs_crypt_stat {int flags; scalar_t__ metadata_size; int /*<<< orphan*/  iv_bytes; int /*<<< orphan*/  extent_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECRYPTFS_DEFAULT_EXTENT_SIZE ; 
 int /*<<< orphan*/  ECRYPTFS_DEFAULT_IV_BYTES ; 
 int ECRYPTFS_METADATA_IN_XATTR ; 
 scalar_t__ ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  set_extent_mask_and_shift (struct ecryptfs_crypt_stat*) ; 

void ecryptfs_set_default_sizes(struct ecryptfs_crypt_stat *crypt_stat)
{
	/* Default values; may be overwritten as we are parsing the
	 * packets. */
	crypt_stat->extent_size = ECRYPTFS_DEFAULT_EXTENT_SIZE;
	set_extent_mask_and_shift(crypt_stat);
	crypt_stat->iv_bytes = ECRYPTFS_DEFAULT_IV_BYTES;
	if (crypt_stat->flags & ECRYPTFS_METADATA_IN_XATTR)
		crypt_stat->metadata_size = ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
	else {
		if (PAGE_SIZE <= ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE)
			crypt_stat->metadata_size =
				ECRYPTFS_MINIMUM_HEADER_EXTENT_SIZE;
		else
			crypt_stat->metadata_size = PAGE_SIZE;
	}
}