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
typedef  int /*<<< orphan*/  uint64_t ;
struct signature_hdr {scalar_t__ algo; scalar_t__ keyid; } ;
struct shash_desc {int /*<<< orphan*/  tfm; } ;
struct key {int dummy; } ;
typedef  struct key* key_ref_t ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 struct key* ERR_CAST (struct key*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 scalar_t__ PUBKEY_ALGO_RSA ; 
 int SHA1_DIGEST_SIZE ; 
 int /*<<< orphan*/  __be64_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ crypto_shash_descsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_shash_final (struct shash_desc*,unsigned char*) ; 
 int /*<<< orphan*/  crypto_shash_init (struct shash_desc*) ; 
 int /*<<< orphan*/  crypto_shash_update (struct shash_desc*,char const*,int) ; 
 int digsig_verify_rsa (struct key*,char const*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 struct key* key_ref_to_ptr (struct key*) ; 
 int /*<<< orphan*/  key_type_user ; 
 struct key* keyring_search (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (struct shash_desc*) ; 
 struct shash_desc* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_key_ref (struct key*,unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 struct key* request_key (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shash ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

int digsig_verify(struct key *keyring, const char *sig, int siglen,
						const char *data, int datalen)
{
	int err = -ENOMEM;
	struct signature_hdr *sh = (struct signature_hdr *)sig;
	struct shash_desc *desc = NULL;
	unsigned char hash[SHA1_DIGEST_SIZE];
	struct key *key;
	char name[20];

	if (siglen < sizeof(*sh) + 2)
		return -EINVAL;

	if (sh->algo != PUBKEY_ALGO_RSA)
		return -ENOTSUPP;

	sprintf(name, "%llX", __be64_to_cpup((uint64_t *)sh->keyid));

	if (keyring) {
		/* search in specific keyring */
		key_ref_t kref;
		kref = keyring_search(make_key_ref(keyring, 1UL),
				      &key_type_user, name, true);
		if (IS_ERR(kref))
			key = ERR_CAST(kref);
		else
			key = key_ref_to_ptr(kref);
	} else {
		key = request_key(&key_type_user, name, NULL);
	}
	if (IS_ERR(key)) {
		pr_err("key not found, id: %s\n", name);
		return PTR_ERR(key);
	}

	desc = kzalloc(sizeof(*desc) + crypto_shash_descsize(shash),
		       GFP_KERNEL);
	if (!desc)
		goto err;

	desc->tfm = shash;

	crypto_shash_init(desc);
	crypto_shash_update(desc, data, datalen);
	crypto_shash_update(desc, sig, sizeof(*sh));
	crypto_shash_final(desc, hash);

	kfree(desc);

	/* pass signature mpis address */
	err = digsig_verify_rsa(key, sig + sizeof(*sh), siglen - sizeof(*sh),
			     hash, sizeof(hash));

err:
	key_put(key);

	return err ? -EINVAL : 0;
}