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
struct key {int /*<<< orphan*/  sem; } ;
struct inode {TYPE_2__* i_sb; } ;
struct fscrypt_key {int /*<<< orphan*/  raw; } ;
struct fscrypt_context {int /*<<< orphan*/  master_key_descriptor; } ;
struct TYPE_4__ {TYPE_1__* s_cop; } ;
struct TYPE_3__ {scalar_t__ key_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ FS_KEY_DESC_PREFIX ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int derive_key_aes (int /*<<< orphan*/ ,struct fscrypt_context const*,int /*<<< orphan*/ *,unsigned int) ; 
 struct key* find_and_lock_process_key (scalar_t__,int /*<<< orphan*/ ,unsigned int,struct fscrypt_key const**) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_and_derive_key(const struct inode *inode,
			       const struct fscrypt_context *ctx,
			       u8 *derived_key, unsigned int derived_keysize)
{
	struct key *key;
	const struct fscrypt_key *payload;
	int err;

	key = find_and_lock_process_key(FS_KEY_DESC_PREFIX,
					ctx->master_key_descriptor,
					derived_keysize, &payload);
	if (key == ERR_PTR(-ENOKEY) && inode->i_sb->s_cop->key_prefix) {
		key = find_and_lock_process_key(inode->i_sb->s_cop->key_prefix,
						ctx->master_key_descriptor,
						derived_keysize, &payload);
	}
	if (IS_ERR(key))
		return PTR_ERR(key);
	err = derive_key_aes(payload->raw, ctx, derived_key, derived_keysize);
	up_read(&key->sem);
	key_put(key);
	return err;
}