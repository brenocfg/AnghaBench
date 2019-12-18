#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct xdr_netobj {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct crypto_shash {int dummy; } ;
struct TYPE_5__ {struct crypto_shash* tfm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  SHASH_DESC_ON_STACK (TYPE_1__*,struct crypto_shash*) ; 
 struct crypto_shash* crypto_alloc_shash (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int crypto_shash_digest (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_shash_digestsize (struct crypto_shash*) ; 
 TYPE_1__* desc ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md5_to_hex (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shash_desc_zero (TYPE_1__*) ; 

__attribute__((used)) static int
nfs4_make_rec_clidname(char *dname, const struct xdr_netobj *clname)
{
	struct xdr_netobj cksum;
	struct crypto_shash *tfm;
	int status;

	dprintk("NFSD: nfs4_make_rec_clidname for %.*s\n",
			clname->len, clname->data);
	tfm = crypto_alloc_shash("md5", 0, 0);
	if (IS_ERR(tfm)) {
		status = PTR_ERR(tfm);
		goto out_no_tfm;
	}

	cksum.len = crypto_shash_digestsize(tfm);
	cksum.data = kmalloc(cksum.len, GFP_KERNEL);
	if (cksum.data == NULL) {
		status = -ENOMEM;
 		goto out;
	}

	{
		SHASH_DESC_ON_STACK(desc, tfm);

		desc->tfm = tfm;

		status = crypto_shash_digest(desc, clname->data, clname->len,
					     cksum.data);
		shash_desc_zero(desc);
	}

	if (status)
		goto out;

	md5_to_hex(dname, cksum.data);

	status = 0;
out:
	kfree(cksum.data);
	crypto_free_shash(tfm);
out_no_tfm:
	return status;
}