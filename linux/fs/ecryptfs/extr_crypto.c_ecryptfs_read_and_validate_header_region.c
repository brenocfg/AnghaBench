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
typedef  int /*<<< orphan*/  u8 ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ECRYPTFS_FILE_SIZE_BYTES ; 
 int ECRYPTFS_SIZE_AND_MARKER_BYTES ; 
 int EINVAL ; 
 int /*<<< orphan*/  ecryptfs_i_size_init (int /*<<< orphan*/ *,struct inode*) ; 
 int ecryptfs_read_lower (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct inode*) ; 
 int ecryptfs_validate_marker (int /*<<< orphan*/ *) ; 

int ecryptfs_read_and_validate_header_region(struct inode *inode)
{
	u8 file_size[ECRYPTFS_SIZE_AND_MARKER_BYTES];
	u8 *marker = file_size + ECRYPTFS_FILE_SIZE_BYTES;
	int rc;

	rc = ecryptfs_read_lower(file_size, 0, ECRYPTFS_SIZE_AND_MARKER_BYTES,
				 inode);
	if (rc < 0)
		return rc;
	else if (rc < ECRYPTFS_SIZE_AND_MARKER_BYTES)
		return -EINVAL;
	rc = ecryptfs_validate_marker(marker);
	if (!rc)
		ecryptfs_i_size_init(file_size, inode);
	return rc;
}