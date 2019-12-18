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
struct super_block {scalar_t__ s_master_keys; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int FSCRYPT_FS_KEYRING_DESCRIPTION_SIZE ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_SEARCH ; 
 int KEY_USR_READ ; 
 int KEY_USR_SEARCH ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  format_fs_keyring_description (char*,struct super_block*) ; 
 struct key* keyring_alloc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_store_release (scalar_t__*,struct key*) ; 

__attribute__((used)) static int allocate_filesystem_keyring(struct super_block *sb)
{
	char description[FSCRYPT_FS_KEYRING_DESCRIPTION_SIZE];
	struct key *keyring;

	if (sb->s_master_keys)
		return 0;

	format_fs_keyring_description(description, sb);
	keyring = keyring_alloc(description, GLOBAL_ROOT_UID, GLOBAL_ROOT_GID,
				current_cred(), KEY_POS_SEARCH |
				  KEY_USR_SEARCH | KEY_USR_READ | KEY_USR_VIEW,
				KEY_ALLOC_NOT_IN_QUOTA, NULL, NULL);
	if (IS_ERR(keyring))
		return PTR_ERR(keyring);

	/* Pairs with READ_ONCE() in fscrypt_find_master_key() */
	smp_store_release(&sb->s_master_keys, keyring);
	return 0;
}