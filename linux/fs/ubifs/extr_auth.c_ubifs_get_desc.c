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
struct ubifs_info {int dummy; } ;
struct shash_desc {struct crypto_shash* tfm; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct shash_desc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ crypto_shash_descsize (struct crypto_shash*) ; 
 int crypto_shash_init (struct shash_desc*) ; 
 int /*<<< orphan*/  kfree (struct shash_desc*) ; 
 struct shash_desc* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_authenticated (struct ubifs_info const*) ; 

__attribute__((used)) static struct shash_desc *ubifs_get_desc(const struct ubifs_info *c,
					 struct crypto_shash *tfm)
{
	struct shash_desc *desc;
	int err;

	if (!ubifs_authenticated(c))
		return NULL;

	desc = kmalloc(sizeof(*desc) + crypto_shash_descsize(tfm), GFP_KERNEL);
	if (!desc)
		return ERR_PTR(-ENOMEM);

	desc->tfm = tfm;

	err = crypto_shash_init(desc);
	if (err) {
		kfree(desc);
		return ERR_PTR(err);
	}

	return desc;
}