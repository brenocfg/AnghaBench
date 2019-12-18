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
struct inode {int dummy; } ;
struct fscrypt_symlink_data {int dummy; } ;
struct fscrypt_str {int len; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOKEY ; 
 int /*<<< orphan*/  fscrypt_fname_encrypted_size (struct inode*,unsigned int,unsigned int,int*) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  fscrypt_has_encryption_key (struct inode*) ; 

int __fscrypt_prepare_symlink(struct inode *dir, unsigned int len,
			      unsigned int max_len,
			      struct fscrypt_str *disk_link)
{
	int err;

	/*
	 * To calculate the size of the encrypted symlink target we need to know
	 * the amount of NUL padding, which is determined by the flags set in
	 * the encryption policy which will be inherited from the directory.
	 * The easiest way to get access to this is to just load the directory's
	 * fscrypt_info, since we'll need it to create the dir_entry anyway.
	 *
	 * Note: in test_dummy_encryption mode, @dir may be unencrypted.
	 */
	err = fscrypt_get_encryption_info(dir);
	if (err)
		return err;
	if (!fscrypt_has_encryption_key(dir))
		return -ENOKEY;

	/*
	 * Calculate the size of the encrypted symlink and verify it won't
	 * exceed max_len.  Note that for historical reasons, encrypted symlink
	 * targets are prefixed with the ciphertext length, despite this
	 * actually being redundant with i_size.  This decreases by 2 bytes the
	 * longest symlink target we can accept.
	 *
	 * We could recover 1 byte by not counting a null terminator, but
	 * counting it (even though it is meaningless for ciphertext) is simpler
	 * for now since filesystems will assume it is there and subtract it.
	 */
	if (!fscrypt_fname_encrypted_size(dir, len,
					  max_len - sizeof(struct fscrypt_symlink_data),
					  &disk_link->len))
		return -ENAMETOOLONG;
	disk_link->len += sizeof(struct fscrypt_symlink_data);

	disk_link->name = NULL;
	return 0;
}