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
struct key {int dummy; } ;
struct fscrypt_master_key_secret {int dummy; } ;
struct fscrypt_key_specifier {scalar_t__ type; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_decrypted_inodes_lock; int /*<<< orphan*/  mk_decrypted_inodes; int /*<<< orphan*/  mk_refcount; int /*<<< orphan*/  mk_secret_sem; int /*<<< orphan*/  mk_secret; struct fscrypt_key_specifier mk_spec; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER ; 
 int FSCRYPT_MK_DESCRIPTION_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_ALLOC_NOT_IN_QUOTA ; 
 int KEY_POS_SEARCH ; 
 int KEY_USR_SEARCH ; 
 int KEY_USR_VIEW ; 
 int PTR_ERR (struct key*) ; 
 int add_master_key_user (struct fscrypt_master_key*) ; 
 int allocate_master_key_users_keyring (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  current_cred () ; 
 int /*<<< orphan*/  format_mk_description (char*,struct fscrypt_key_specifier const*) ; 
 int /*<<< orphan*/  free_master_key (struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct key* key_alloc (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int key_instantiate_and_link (struct key*,struct fscrypt_master_key*,int,struct key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_fscrypt ; 
 struct fscrypt_master_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  move_master_key_secret (int /*<<< orphan*/ *,struct fscrypt_master_key_secret*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_new_master_key(struct fscrypt_master_key_secret *secret,
			      const struct fscrypt_key_specifier *mk_spec,
			      struct key *keyring)
{
	struct fscrypt_master_key *mk;
	char description[FSCRYPT_MK_DESCRIPTION_SIZE];
	struct key *key;
	int err;

	mk = kzalloc(sizeof(*mk), GFP_KERNEL);
	if (!mk)
		return -ENOMEM;

	mk->mk_spec = *mk_spec;

	move_master_key_secret(&mk->mk_secret, secret);
	init_rwsem(&mk->mk_secret_sem);

	refcount_set(&mk->mk_refcount, 1); /* secret is present */
	INIT_LIST_HEAD(&mk->mk_decrypted_inodes);
	spin_lock_init(&mk->mk_decrypted_inodes_lock);

	if (mk_spec->type == FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER) {
		err = allocate_master_key_users_keyring(mk);
		if (err)
			goto out_free_mk;
		err = add_master_key_user(mk);
		if (err)
			goto out_free_mk;
	}

	/*
	 * Note that we don't charge this key to anyone's quota, since when
	 * ->mk_users is in use those keys are charged instead, and otherwise
	 * (when ->mk_users isn't in use) only root can add these keys.
	 */
	format_mk_description(description, mk_spec);
	key = key_alloc(&key_type_fscrypt, description,
			GLOBAL_ROOT_UID, GLOBAL_ROOT_GID, current_cred(),
			KEY_POS_SEARCH | KEY_USR_SEARCH | KEY_USR_VIEW,
			KEY_ALLOC_NOT_IN_QUOTA, NULL);
	if (IS_ERR(key)) {
		err = PTR_ERR(key);
		goto out_free_mk;
	}
	err = key_instantiate_and_link(key, mk, sizeof(*mk), keyring, NULL);
	key_put(key);
	if (err)
		goto out_free_mk;

	return 0;

out_free_mk:
	free_master_key(mk);
	return err;
}