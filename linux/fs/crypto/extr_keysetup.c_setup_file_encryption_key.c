#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {struct fscrypt_master_key** data; } ;
struct key {TYPE_4__ payload; } ;
struct TYPE_16__ {int /*<<< orphan*/  raw; int /*<<< orphan*/  size; } ;
struct fscrypt_master_key {int /*<<< orphan*/  mk_secret_sem; TYPE_8__ mk_secret; } ;
struct TYPE_13__ {int /*<<< orphan*/  identifier; int /*<<< orphan*/  descriptor; } ;
struct fscrypt_key_specifier {TYPE_5__ u; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  master_key_identifier; } ;
struct TYPE_9__ {int /*<<< orphan*/  master_key_descriptor; } ;
struct TYPE_15__ {int version; TYPE_2__ v2; TYPE_1__ v1; } ;
struct fscrypt_info {TYPE_7__ ci_policy; TYPE_6__* ci_mode; TYPE_3__* ci_inode; } ;
struct TYPE_14__ {int /*<<< orphan*/  keysize; } ;
struct TYPE_11__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOKEY ; 
 struct key* ERR_PTR (int) ; 
 int /*<<< orphan*/  FSCRYPT_KEY_DESCRIPTOR_SIZE ; 
 int /*<<< orphan*/  FSCRYPT_KEY_IDENTIFIER_SIZE ; 
 int /*<<< orphan*/  FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR ; 
 int /*<<< orphan*/  FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER ; 
#define  FSCRYPT_POLICY_V1 129 
#define  FSCRYPT_POLICY_V2 128 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct key* fscrypt_find_master_key (int /*<<< orphan*/ ,struct fscrypt_key_specifier*) ; 
 int fscrypt_setup_v1_file_key (struct fscrypt_info*,int /*<<< orphan*/ ) ; 
 int fscrypt_setup_v1_file_key_via_subscribed_keyrings (struct fscrypt_info*) ; 
 int fscrypt_setup_v2_file_key (struct fscrypt_info*,struct fscrypt_master_key*) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_master_key_secret_present (TYPE_8__*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  master_key_spec_len (struct fscrypt_key_specifier*) ; 
 int /*<<< orphan*/  master_key_spec_type (struct fscrypt_key_specifier*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setup_file_encryption_key(struct fscrypt_info *ci,
				     struct key **master_key_ret)
{
	struct key *key;
	struct fscrypt_master_key *mk = NULL;
	struct fscrypt_key_specifier mk_spec;
	int err;

	switch (ci->ci_policy.version) {
	case FSCRYPT_POLICY_V1:
		mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_DESCRIPTOR;
		memcpy(mk_spec.u.descriptor,
		       ci->ci_policy.v1.master_key_descriptor,
		       FSCRYPT_KEY_DESCRIPTOR_SIZE);
		break;
	case FSCRYPT_POLICY_V2:
		mk_spec.type = FSCRYPT_KEY_SPEC_TYPE_IDENTIFIER;
		memcpy(mk_spec.u.identifier,
		       ci->ci_policy.v2.master_key_identifier,
		       FSCRYPT_KEY_IDENTIFIER_SIZE);
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	key = fscrypt_find_master_key(ci->ci_inode->i_sb, &mk_spec);
	if (IS_ERR(key)) {
		if (key != ERR_PTR(-ENOKEY) ||
		    ci->ci_policy.version != FSCRYPT_POLICY_V1)
			return PTR_ERR(key);

		/*
		 * As a legacy fallback for v1 policies, search for the key in
		 * the current task's subscribed keyrings too.  Don't move this
		 * to before the search of ->s_master_keys, since users
		 * shouldn't be able to override filesystem-level keys.
		 */
		return fscrypt_setup_v1_file_key_via_subscribed_keyrings(ci);
	}

	mk = key->payload.data[0];
	down_read(&mk->mk_secret_sem);

	/* Has the secret been removed (via FS_IOC_REMOVE_ENCRYPTION_KEY)? */
	if (!is_master_key_secret_present(&mk->mk_secret)) {
		err = -ENOKEY;
		goto out_release_key;
	}

	/*
	 * Require that the master key be at least as long as the derived key.
	 * Otherwise, the derived key cannot possibly contain as much entropy as
	 * that required by the encryption mode it will be used for.  For v1
	 * policies it's also required for the KDF to work at all.
	 */
	if (mk->mk_secret.size < ci->ci_mode->keysize) {
		fscrypt_warn(NULL,
			     "key with %s %*phN is too short (got %u bytes, need %u+ bytes)",
			     master_key_spec_type(&mk_spec),
			     master_key_spec_len(&mk_spec), (u8 *)&mk_spec.u,
			     mk->mk_secret.size, ci->ci_mode->keysize);
		err = -ENOKEY;
		goto out_release_key;
	}

	switch (ci->ci_policy.version) {
	case FSCRYPT_POLICY_V1:
		err = fscrypt_setup_v1_file_key(ci, mk->mk_secret.raw);
		break;
	case FSCRYPT_POLICY_V2:
		err = fscrypt_setup_v2_file_key(ci, mk);
		break;
	default:
		WARN_ON(1);
		err = -EINVAL;
		break;
	}
	if (err)
		goto out_release_key;

	*master_key_ret = key;
	return 0;

out_release_key:
	up_read(&mk->mk_secret_sem);
	key_put(key);
	return err;
}