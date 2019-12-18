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
typedef  union fscrypt_policy {int dummy; } fscrypt_policy ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ENCRYPTED (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int fscrypt_get_encryption_info (struct inode*) ; 
 int fscrypt_get_policy (struct inode*,union fscrypt_policy*) ; 
 int fscrypt_policies_equal (union fscrypt_policy*,union fscrypt_policy*) ; 

int fscrypt_has_permitted_context(struct inode *parent, struct inode *child)
{
	union fscrypt_policy parent_policy, child_policy;
	int err;

	/* No restrictions on file types which are never encrypted */
	if (!S_ISREG(child->i_mode) && !S_ISDIR(child->i_mode) &&
	    !S_ISLNK(child->i_mode))
		return 1;

	/* No restrictions if the parent directory is unencrypted */
	if (!IS_ENCRYPTED(parent))
		return 1;

	/* Encrypted directories must not contain unencrypted files */
	if (!IS_ENCRYPTED(child))
		return 0;

	/*
	 * Both parent and child are encrypted, so verify they use the same
	 * encryption policy.  Compare the fscrypt_info structs if the keys are
	 * available, otherwise retrieve and compare the fscrypt_contexts.
	 *
	 * Note that the fscrypt_context retrieval will be required frequently
	 * when accessing an encrypted directory tree without the key.
	 * Performance-wise this is not a big deal because we already don't
	 * really optimize for file access without the key (to the extent that
	 * such access is even possible), given that any attempted access
	 * already causes a fscrypt_context retrieval and keyring search.
	 *
	 * In any case, if an unexpected error occurs, fall back to "forbidden".
	 */

	err = fscrypt_get_encryption_info(parent);
	if (err)
		return 0;
	err = fscrypt_get_encryption_info(child);
	if (err)
		return 0;

	err = fscrypt_get_policy(parent, &parent_policy);
	if (err)
		return 0;

	err = fscrypt_get_policy(child, &child_policy);
	if (err)
		return 0;

	return fscrypt_policies_equal(&parent_policy, &child_policy);
}