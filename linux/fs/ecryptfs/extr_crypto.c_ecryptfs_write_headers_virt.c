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
struct ecryptfs_crypt_stat {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 size_t ECRYPTFS_FILE_SIZE_BYTES ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int ecryptfs_generate_key_packet_set (char*,struct ecryptfs_crypt_stat*,struct dentry*,size_t*,size_t) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ecryptfs_write_crypt_stat_flags (char*,struct ecryptfs_crypt_stat*,size_t*) ; 
 int /*<<< orphan*/  ecryptfs_write_header_metadata (char*,struct ecryptfs_crypt_stat*,size_t*) ; 
 int /*<<< orphan*/  write_ecryptfs_marker (char*,size_t*) ; 

__attribute__((used)) static int ecryptfs_write_headers_virt(char *page_virt, size_t max,
				       size_t *size,
				       struct ecryptfs_crypt_stat *crypt_stat,
				       struct dentry *ecryptfs_dentry)
{
	int rc;
	size_t written;
	size_t offset;

	offset = ECRYPTFS_FILE_SIZE_BYTES;
	write_ecryptfs_marker((page_virt + offset), &written);
	offset += written;
	ecryptfs_write_crypt_stat_flags((page_virt + offset), crypt_stat,
					&written);
	offset += written;
	ecryptfs_write_header_metadata((page_virt + offset), crypt_stat,
				       &written);
	offset += written;
	rc = ecryptfs_generate_key_packet_set((page_virt + offset), crypt_stat,
					      ecryptfs_dentry, &written,
					      max - offset);
	if (rc)
		ecryptfs_printk(KERN_WARNING, "Error generating key packet "
				"set; rc = [%d]\n", rc);
	if (size) {
		offset += written;
		*size = offset;
	}
	return rc;
}