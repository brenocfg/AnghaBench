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
struct user_key_payload {int datalen; scalar_t__ data; } ;
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/  description; } ;
struct fscrypt_key {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct key* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSCRYPT_KEY_DESCRIPTOR_SIZE ; 
 int FSCRYPT_MAX_KEY_SIZE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscrypt_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_logon ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct key* request_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

__attribute__((used)) static struct key *
find_and_lock_process_key(const char *prefix,
			  const u8 descriptor[FSCRYPT_KEY_DESCRIPTOR_SIZE],
			  unsigned int min_keysize,
			  const struct fscrypt_key **payload_ret)
{
	char *description;
	struct key *key;
	const struct user_key_payload *ukp;
	const struct fscrypt_key *payload;

	description = kasprintf(GFP_NOFS, "%s%*phN", prefix,
				FSCRYPT_KEY_DESCRIPTOR_SIZE, descriptor);
	if (!description)
		return ERR_PTR(-ENOMEM);

	key = request_key(&key_type_logon, description, NULL);
	kfree(description);
	if (IS_ERR(key))
		return key;

	down_read(&key->sem);
	ukp = user_key_payload_locked(key);

	if (!ukp) /* was the key revoked before we acquired its semaphore? */
		goto invalid;

	payload = (const struct fscrypt_key *)ukp->data;

	if (ukp->datalen != sizeof(struct fscrypt_key) ||
	    payload->size < 1 || payload->size > FSCRYPT_MAX_KEY_SIZE) {
		fscrypt_warn(NULL,
			     "key with description '%s' has invalid payload",
			     key->description);
		goto invalid;
	}

	if (payload->size < min_keysize) {
		fscrypt_warn(NULL,
			     "key with description '%s' is too short (got %u bytes, need %u+ bytes)",
			     key->description, payload->size, min_keysize);
		goto invalid;
	}

	*payload_ret = payload;
	return key;

invalid:
	up_read(&key->sem);
	key_put(key);
	return ERR_PTR(-ENOKEY);
}