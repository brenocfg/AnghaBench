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
struct fscrypt_symlink_data {int /*<<< orphan*/  len; scalar_t__ encrypted_path; } ;
struct fscrypt_str {unsigned char* name; int len; } ;
struct delayed_call {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 char const* ERR_PTR (int) ; 
 int EUCLEAN ; 
 int /*<<< orphan*/  IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ WARN_ON (int) ; 
 int fscrypt_fname_alloc_buffer (struct inode*,int,struct fscrypt_str*) ; 
 int fscrypt_fname_disk_to_usr (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fscrypt_str*,struct fscrypt_str*) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  kfree_link ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_delayed_call (struct delayed_call*,int /*<<< orphan*/ ,char*) ; 

const char *fscrypt_get_symlink(struct inode *inode, const void *caddr,
				unsigned int max_size,
				struct delayed_call *done)
{
	const struct fscrypt_symlink_data *sd;
	struct fscrypt_str cstr, pstr;
	int err;

	/* This is for encrypted symlinks only */
	if (WARN_ON(!IS_ENCRYPTED(inode)))
		return ERR_PTR(-EINVAL);

	/*
	 * Try to set up the symlink's encryption key, but we can continue
	 * regardless of whether the key is available or not.
	 */
	err = fscrypt_get_encryption_info(inode);
	if (err)
		return ERR_PTR(err);

	/*
	 * For historical reasons, encrypted symlink targets are prefixed with
	 * the ciphertext length, even though this is redundant with i_size.
	 */

	if (max_size < sizeof(*sd))
		return ERR_PTR(-EUCLEAN);
	sd = caddr;
	cstr.name = (unsigned char *)sd->encrypted_path;
	cstr.len = le16_to_cpu(sd->len);

	if (cstr.len == 0)
		return ERR_PTR(-EUCLEAN);

	if (cstr.len + sizeof(*sd) - 1 > max_size)
		return ERR_PTR(-EUCLEAN);

	err = fscrypt_fname_alloc_buffer(inode, cstr.len, &pstr);
	if (err)
		return ERR_PTR(err);

	err = fscrypt_fname_disk_to_usr(inode, 0, 0, &cstr, &pstr);
	if (err)
		goto err_kfree;

	err = -EUCLEAN;
	if (pstr.name[0] == '\0')
		goto err_kfree;

	pstr.name[pstr.len] = '\0';
	set_delayed_call(done, kfree_link, pstr.name);
	return pstr.name;

err_kfree:
	kfree(pstr.name);
	return ERR_PTR(err);
}