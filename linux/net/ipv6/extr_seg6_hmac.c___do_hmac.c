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
struct shash_desc {struct crypto_shash* tfm; } ;
struct seg6_hmac_info {int /*<<< orphan*/  slen; int /*<<< orphan*/  secret; int /*<<< orphan*/  alg_id; } ;
struct seg6_hmac_algo {int /*<<< orphan*/  shashs; int /*<<< orphan*/  tfms; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 struct seg6_hmac_algo* __hmac_get_algo (int /*<<< orphan*/ ) ; 
 int crypto_shash_digest (struct shash_desc*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int crypto_shash_digestsize (struct crypto_shash*) ; 
 int crypto_shash_setkey (struct crypto_shash*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 void** this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __do_hmac(struct seg6_hmac_info *hinfo, const char *text, u8 psize,
		     u8 *output, int outlen)
{
	struct seg6_hmac_algo *algo;
	struct crypto_shash *tfm;
	struct shash_desc *shash;
	int ret, dgsize;

	algo = __hmac_get_algo(hinfo->alg_id);
	if (!algo)
		return -ENOENT;

	tfm = *this_cpu_ptr(algo->tfms);

	dgsize = crypto_shash_digestsize(tfm);
	if (dgsize > outlen) {
		pr_debug("sr-ipv6: __do_hmac: digest size too big (%d / %d)\n",
			 dgsize, outlen);
		return -ENOMEM;
	}

	ret = crypto_shash_setkey(tfm, hinfo->secret, hinfo->slen);
	if (ret < 0) {
		pr_debug("sr-ipv6: crypto_shash_setkey failed: err %d\n", ret);
		goto failed;
	}

	shash = *this_cpu_ptr(algo->shashs);
	shash->tfm = tfm;

	ret = crypto_shash_digest(shash, text, psize, output);
	if (ret < 0) {
		pr_debug("sr-ipv6: crypto_shash_digest failed: err %d\n", ret);
		goto failed;
	}

	return dgsize;

failed:
	return ret;
}