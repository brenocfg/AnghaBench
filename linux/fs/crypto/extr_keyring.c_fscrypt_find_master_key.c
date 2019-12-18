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
struct super_block {int /*<<< orphan*/  s_master_keys; } ;
struct key {int dummy; } ;
struct fscrypt_key_specifier {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 int FSCRYPT_MK_DESCRIPTION_SIZE ; 
 struct key* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_mk_description (char*,struct fscrypt_key_specifier const*) ; 
 int /*<<< orphan*/  key_type_fscrypt ; 
 struct key* search_fscrypt_keyring (struct key*,int /*<<< orphan*/ *,char*) ; 

struct key *fscrypt_find_master_key(struct super_block *sb,
				    const struct fscrypt_key_specifier *mk_spec)
{
	struct key *keyring;
	char description[FSCRYPT_MK_DESCRIPTION_SIZE];

	/* pairs with smp_store_release() in allocate_filesystem_keyring() */
	keyring = READ_ONCE(sb->s_master_keys);
	if (keyring == NULL)
		return ERR_PTR(-ENOKEY); /* No keyring yet, so no keys yet. */

	format_mk_description(description, mk_spec);
	return search_fscrypt_keyring(keyring, &key_type_fscrypt, description);
}