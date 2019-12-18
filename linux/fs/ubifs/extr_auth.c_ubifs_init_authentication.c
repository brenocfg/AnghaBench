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
struct user_key_payload {int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
struct ubifs_info {char* auth_hash_name; int authenticated; struct key* hash_tfm; struct key* hmac_tfm; struct key* log_hash; void* hmac_desc_len; void* hash_len; int /*<<< orphan*/  auth_key_name; scalar_t__ auth_hash_algo; } ;
struct key {int /*<<< orphan*/  sem; int /*<<< orphan*/ * type; } ;

/* Variables and functions */
 int CRYPTO_MAX_ALG_NAME ; 
 int EINVAL ; 
 int EKEYREVOKED ; 
 int ENOKEY ; 
 int /*<<< orphan*/  HASH_ALGO__LAST ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 void* UBIFS_HASH_ARR_SZ ; 
 void* UBIFS_HMAC_ARR_SZ ; 
 void* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct key*) ; 
 void* crypto_shash_digestsize (struct key*) ; 
 int crypto_shash_setkey (struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_algo_name ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_logon ; 
 scalar_t__ match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct key* request_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  ubifs_err (struct ubifs_info*,char*,...) ; 
 struct key* ubifs_hash_get_desc (struct ubifs_info*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 struct user_key_payload* user_key_payload_locked (struct key*) ; 

int ubifs_init_authentication(struct ubifs_info *c)
{
	struct key *keyring_key;
	const struct user_key_payload *ukp;
	int err;
	char hmac_name[CRYPTO_MAX_ALG_NAME];

	if (!c->auth_hash_name) {
		ubifs_err(c, "authentication hash name needed with authentication");
		return -EINVAL;
	}

	c->auth_hash_algo = match_string(hash_algo_name, HASH_ALGO__LAST,
					 c->auth_hash_name);
	if ((int)c->auth_hash_algo < 0) {
		ubifs_err(c, "Unknown hash algo %s specified",
			  c->auth_hash_name);
		return -EINVAL;
	}

	snprintf(hmac_name, CRYPTO_MAX_ALG_NAME, "hmac(%s)",
		 c->auth_hash_name);

	keyring_key = request_key(&key_type_logon, c->auth_key_name, NULL);

	if (IS_ERR(keyring_key)) {
		ubifs_err(c, "Failed to request key: %ld",
			  PTR_ERR(keyring_key));
		return PTR_ERR(keyring_key);
	}

	down_read(&keyring_key->sem);

	if (keyring_key->type != &key_type_logon) {
		ubifs_err(c, "key type must be logon");
		err = -ENOKEY;
		goto out;
	}

	ukp = user_key_payload_locked(keyring_key);
	if (!ukp) {
		/* key was revoked before we acquired its semaphore */
		err = -EKEYREVOKED;
		goto out;
	}

	c->hash_tfm = crypto_alloc_shash(c->auth_hash_name, 0, 0);
	if (IS_ERR(c->hash_tfm)) {
		err = PTR_ERR(c->hash_tfm);
		ubifs_err(c, "Can not allocate %s: %d",
			  c->auth_hash_name, err);
		goto out;
	}

	c->hash_len = crypto_shash_digestsize(c->hash_tfm);
	if (c->hash_len > UBIFS_HASH_ARR_SZ) {
		ubifs_err(c, "hash %s is bigger than maximum allowed hash size (%d > %d)",
			  c->auth_hash_name, c->hash_len, UBIFS_HASH_ARR_SZ);
		err = -EINVAL;
		goto out_free_hash;
	}

	c->hmac_tfm = crypto_alloc_shash(hmac_name, 0, 0);
	if (IS_ERR(c->hmac_tfm)) {
		err = PTR_ERR(c->hmac_tfm);
		ubifs_err(c, "Can not allocate %s: %d", hmac_name, err);
		goto out_free_hash;
	}

	c->hmac_desc_len = crypto_shash_digestsize(c->hmac_tfm);
	if (c->hmac_desc_len > UBIFS_HMAC_ARR_SZ) {
		ubifs_err(c, "hmac %s is bigger than maximum allowed hmac size (%d > %d)",
			  hmac_name, c->hmac_desc_len, UBIFS_HMAC_ARR_SZ);
		err = -EINVAL;
		goto out_free_hash;
	}

	err = crypto_shash_setkey(c->hmac_tfm, ukp->data, ukp->datalen);
	if (err)
		goto out_free_hmac;

	c->authenticated = true;

	c->log_hash = ubifs_hash_get_desc(c);
	if (IS_ERR(c->log_hash))
		goto out_free_hmac;

	err = 0;

out_free_hmac:
	if (err)
		crypto_free_shash(c->hmac_tfm);
out_free_hash:
	if (err)
		crypto_free_shash(c->hash_tfm);
out:
	up_read(&keyring_key->sem);
	key_put(keyring_key);

	return err;
}