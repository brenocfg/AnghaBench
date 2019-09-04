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
typedef  int /*<<< orphan*/  u8 ;
struct key {int dummy; } ;
struct encrypted_key_payload {scalar_t__ master_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOTSUPP ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  KEY_TRUSTED_PREFIX ; 
 scalar_t__ KEY_TRUSTED_PREFIX_LEN ; 
 int /*<<< orphan*/  KEY_USER_PREFIX ; 
 scalar_t__ KEY_USER_PREFIX_LEN ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  dump_master_key (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 struct key* request_trusted_key (scalar_t__,int /*<<< orphan*/  const**,size_t*) ; 
 struct key* request_user_key (scalar_t__,int /*<<< orphan*/  const**,size_t*) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct key *request_master_key(struct encrypted_key_payload *epayload,
				      const u8 **master_key, size_t *master_keylen)
{
	struct key *mkey = ERR_PTR(-EINVAL);

	if (!strncmp(epayload->master_desc, KEY_TRUSTED_PREFIX,
		     KEY_TRUSTED_PREFIX_LEN)) {
		mkey = request_trusted_key(epayload->master_desc +
					   KEY_TRUSTED_PREFIX_LEN,
					   master_key, master_keylen);
	} else if (!strncmp(epayload->master_desc, KEY_USER_PREFIX,
			    KEY_USER_PREFIX_LEN)) {
		mkey = request_user_key(epayload->master_desc +
					KEY_USER_PREFIX_LEN,
					master_key, master_keylen);
	} else
		goto out;

	if (IS_ERR(mkey)) {
		int ret = PTR_ERR(mkey);

		if (ret == -ENOTSUPP)
			pr_info("encrypted_key: key %s not supported",
				epayload->master_desc);
		else
			pr_info("encrypted_key: key %s not found",
				epayload->master_desc);
		goto out;
	}

	dump_master_key(*master_key, *master_keylen);
out:
	return mkey;
}