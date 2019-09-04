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
struct fscrypt_name {int /*<<< orphan*/  disk_name; int /*<<< orphan*/  usr_fname; } ;
struct ext4_filename {int /*<<< orphan*/  disk_name; int /*<<< orphan*/  usr_fname; } ;
struct ext4_dir_entry_2 {int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int fscrypt_match_name (struct fscrypt_name*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool ext4_match(const struct ext4_filename *fname,
			      const struct ext4_dir_entry_2 *de)
{
	struct fscrypt_name f;

	if (!de->inode)
		return false;

	f.usr_fname = fname->usr_fname;
	f.disk_name = fname->disk_name;
#ifdef CONFIG_EXT4_FS_ENCRYPTION
	f.crypto_buf = fname->crypto_buf;
#endif
	return fscrypt_match_name(&f, de->name, de->name_len);
}