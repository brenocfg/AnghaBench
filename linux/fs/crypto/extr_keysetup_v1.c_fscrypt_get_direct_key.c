#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  const* master_key_descriptor; } ;
struct TYPE_5__ {TYPE_1__ v1; } ;
struct fscrypt_info {TYPE_3__* ci_mode; TYPE_2__ ci_policy; int /*<<< orphan*/  ci_inode; } ;
struct fscrypt_direct_key {int /*<<< orphan*/  dk_raw; int /*<<< orphan*/  dk_descriptor; int /*<<< orphan*/ * dk_ctfm; TYPE_3__* dk_mode; int /*<<< orphan*/  dk_refcount; } ;
struct TYPE_6__ {int /*<<< orphan*/  keysize; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fscrypt_direct_key* ERR_PTR (int) ; 
 int /*<<< orphan*/  FSCRYPT_KEY_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 struct fscrypt_direct_key* find_or_insert_direct_key (struct fscrypt_direct_key*,int /*<<< orphan*/  const*,struct fscrypt_info const*) ; 
 int /*<<< orphan*/  free_direct_key (struct fscrypt_direct_key*) ; 
 int /*<<< orphan*/ * fscrypt_allocate_skcipher (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 struct fscrypt_direct_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct fscrypt_direct_key *
fscrypt_get_direct_key(const struct fscrypt_info *ci, const u8 *raw_key)
{
	struct fscrypt_direct_key *dk;
	int err;

	/* Is there already a tfm for this key? */
	dk = find_or_insert_direct_key(NULL, raw_key, ci);
	if (dk)
		return dk;

	/* Nope, allocate one. */
	dk = kzalloc(sizeof(*dk), GFP_NOFS);
	if (!dk)
		return ERR_PTR(-ENOMEM);
	refcount_set(&dk->dk_refcount, 1);
	dk->dk_mode = ci->ci_mode;
	dk->dk_ctfm = fscrypt_allocate_skcipher(ci->ci_mode, raw_key,
						ci->ci_inode);
	if (IS_ERR(dk->dk_ctfm)) {
		err = PTR_ERR(dk->dk_ctfm);
		dk->dk_ctfm = NULL;
		goto err_free_dk;
	}
	memcpy(dk->dk_descriptor, ci->ci_policy.v1.master_key_descriptor,
	       FSCRYPT_KEY_DESCRIPTOR_SIZE);
	memcpy(dk->dk_raw, raw_key, ci->ci_mode->keysize);

	return find_or_insert_direct_key(dk, raw_key, ci);

err_free_dk:
	free_direct_key(dk);
	return ERR_PTR(err);
}