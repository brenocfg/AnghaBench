#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct super_block {int dummy; } ;
struct TYPE_3__ {struct fscrypt_master_key** data; } ;
struct key {TYPE_1__ payload; } ;
struct fscrypt_master_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  identifier; } ;
struct fscrypt_key_specifier {TYPE_2__ u; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_FOWNER ; 
 int ENOKEY ; 
 int /*<<< orphan*/  FSCRYPT_KEY_IDENTIFIER_SIZE ; 
 int /*<<< orphan*/  FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct key* find_master_key_user (struct fscrypt_master_key*) ; 
 struct key* fscrypt_find_master_key (struct super_block*,struct fscrypt_key_specifier*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

int fscrypt_verify_key_added(struct super_block *sb,
			     const u8 identifier[FSCRYPT_KEY_IDENTIFIER_SIZE])
{
	struct fscrypt_key_specifier mk_spec;
	struct key *key, *mk_user;
	struct fscrypt_master_key *mk;
	int err;

	mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER;
	memcpy(mk_spec.u.identifier, identifier, FSCRYPT_KEY_IDENTIFIER_SIZE);

	key = fscrypt_find_master_key(sb, &mk_spec);
	if (IS_ERR(key)) {
		err = PTR_ERR(key);
		goto out;
	}
	mk = key->payload.data[0];
	mk_user = find_master_key_user(mk);
	if (IS_ERR(mk_user)) {
		err = PTR_ERR(mk_user);
	} else {
		key_put(mk_user);
		err = 0;
	}
	key_put(key);
out:
	if (err == -ENOKEY && capable(CAP_FOWNER))
		err = 0;
	return err;
}