#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct extent_crypt_result* data; } ;
struct skcipher_request {TYPE_1__ base; } ;
struct scatterlist {int dummy; } ;
struct extent_crypt_result {int rc; int /*<<< orphan*/  completion; } ;
struct ecryptfs_crypt_stat {int flags; int key_size; int /*<<< orphan*/  cs_tfm_mutex; int /*<<< orphan*/  key; int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EBUSY ; 
 int ECRYPTFS_KEY_SET ; 
 int ECRYPTFS_STRUCT_INITIALIZED ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENCRYPT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int crypto_skcipher_decrypt (struct skcipher_request*) ; 
 int crypto_skcipher_encrypt (struct skcipher_request*) ; 
 int crypto_skcipher_setkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecryptfs_dump_hex (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ecryptfs_printk (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ecryptfs_verbosity ; 
 int /*<<< orphan*/  extent_crypt_complete ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct skcipher_request* skcipher_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skcipher_request_free (struct skcipher_request*) ; 
 int /*<<< orphan*/  skcipher_request_set_callback (struct skcipher_request*,int,int /*<<< orphan*/ ,struct extent_crypt_result*) ; 
 int /*<<< orphan*/  skcipher_request_set_crypt (struct skcipher_request*,struct scatterlist*,struct scatterlist*,int,unsigned char*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int crypt_scatterlist(struct ecryptfs_crypt_stat *crypt_stat,
			     struct scatterlist *dst_sg,
			     struct scatterlist *src_sg, int size,
			     unsigned char *iv, int op)
{
	struct skcipher_request *req = NULL;
	struct extent_crypt_result ecr;
	int rc = 0;

	BUG_ON(!crypt_stat || !crypt_stat->tfm
	       || !(crypt_stat->flags & ECRYPTFS_STRUCT_INITIALIZED));
	if (unlikely(ecryptfs_verbosity > 0)) {
		ecryptfs_printk(KERN_DEBUG, "Key size [%zd]; key:\n",
				crypt_stat->key_size);
		ecryptfs_dump_hex(crypt_stat->key,
				  crypt_stat->key_size);
	}

	init_completion(&ecr.completion);

	mutex_lock(&crypt_stat->cs_tfm_mutex);
	req = skcipher_request_alloc(crypt_stat->tfm, GFP_NOFS);
	if (!req) {
		mutex_unlock(&crypt_stat->cs_tfm_mutex);
		rc = -ENOMEM;
		goto out;
	}

	skcipher_request_set_callback(req,
			CRYPTO_TFM_REQ_MAY_BACKLOG | CRYPTO_TFM_REQ_MAY_SLEEP,
			extent_crypt_complete, &ecr);
	/* Consider doing this once, when the file is opened */
	if (!(crypt_stat->flags & ECRYPTFS_KEY_SET)) {
		rc = crypto_skcipher_setkey(crypt_stat->tfm, crypt_stat->key,
					    crypt_stat->key_size);
		if (rc) {
			ecryptfs_printk(KERN_ERR,
					"Error setting key; rc = [%d]\n",
					rc);
			mutex_unlock(&crypt_stat->cs_tfm_mutex);
			rc = -EINVAL;
			goto out;
		}
		crypt_stat->flags |= ECRYPTFS_KEY_SET;
	}
	mutex_unlock(&crypt_stat->cs_tfm_mutex);
	skcipher_request_set_crypt(req, src_sg, dst_sg, size, iv);
	rc = op == ENCRYPT ? crypto_skcipher_encrypt(req) :
			     crypto_skcipher_decrypt(req);
	if (rc == -EINPROGRESS || rc == -EBUSY) {
		struct extent_crypt_result *ecr = req->base.data;

		wait_for_completion(&ecr->completion);
		rc = ecr->rc;
		reinit_completion(&ecr->completion);
	}
out:
	skcipher_request_free(req);
	return rc;
}