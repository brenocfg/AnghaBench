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
struct ceph_crypto_key {int type; int /*<<< orphan*/  len; int /*<<< orphan*/ * key; int /*<<< orphan*/ * tfm; } ;

/* Variables and functions */
#define  CEPH_CRYPTO_AES 129 
#define  CEPH_CRYPTO_NONE 128 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_crypto_key_destroy (struct ceph_crypto_key*) ; 
 int /*<<< orphan*/ * crypto_alloc_sync_skcipher (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_sync_skcipher_setkey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * kmemdup (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memalloc_noio_restore (unsigned int) ; 
 unsigned int memalloc_noio_save () ; 

__attribute__((used)) static int set_secret(struct ceph_crypto_key *key, void *buf)
{
	unsigned int noio_flag;
	int ret;

	key->key = NULL;
	key->tfm = NULL;

	switch (key->type) {
	case CEPH_CRYPTO_NONE:
		return 0; /* nothing to do */
	case CEPH_CRYPTO_AES:
		break;
	default:
		return -ENOTSUPP;
	}

	if (!key->len)
		return -EINVAL;

	key->key = kmemdup(buf, key->len, GFP_NOIO);
	if (!key->key) {
		ret = -ENOMEM;
		goto fail;
	}

	/* crypto_alloc_sync_skcipher() allocates with GFP_KERNEL */
	noio_flag = memalloc_noio_save();
	key->tfm = crypto_alloc_sync_skcipher("cbc(aes)", 0, 0);
	memalloc_noio_restore(noio_flag);
	if (IS_ERR(key->tfm)) {
		ret = PTR_ERR(key->tfm);
		key->tfm = NULL;
		goto fail;
	}

	ret = crypto_sync_skcipher_setkey(key->tfm, key->key, key->len);
	if (ret)
		goto fail;

	return 0;

fail:
	ceph_crypto_key_destroy(key);
	return ret;
}