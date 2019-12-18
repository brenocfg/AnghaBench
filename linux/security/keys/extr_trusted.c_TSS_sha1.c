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
struct sdesc {int /*<<< orphan*/  shash; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sdesc*) ; 
 int PTR_ERR (struct sdesc*) ; 
 int crypto_shash_digest (int /*<<< orphan*/ *,unsigned char const*,unsigned int,unsigned char*) ; 
 int /*<<< orphan*/  hash_alg ; 
 int /*<<< orphan*/  hashalg ; 
 struct sdesc* init_sdesc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzfree (struct sdesc*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int TSS_sha1(const unsigned char *data, unsigned int datalen,
		    unsigned char *digest)
{
	struct sdesc *sdesc;
	int ret;

	sdesc = init_sdesc(hashalg);
	if (IS_ERR(sdesc)) {
		pr_info("trusted_key: can't alloc %s\n", hash_alg);
		return PTR_ERR(sdesc);
	}

	ret = crypto_shash_digest(&sdesc->shash, data, datalen, digest);
	kzfree(sdesc);
	return ret;
}