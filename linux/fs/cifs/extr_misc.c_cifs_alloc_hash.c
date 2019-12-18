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
struct shash_desc {int dummy; } ;
struct TYPE_2__ {struct crypto_shash* tfm; } ;
struct sdesc {TYPE_1__ shash; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct crypto_shash*) ; 
 int PTR_ERR (struct crypto_shash*) ; 
 int /*<<< orphan*/  VFS ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,char const*) ; 
 struct crypto_shash* crypto_alloc_shash (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_free_shash (struct crypto_shash*) ; 
 int crypto_shash_descsize (struct crypto_shash*) ; 
 struct sdesc* kmalloc (size_t,int /*<<< orphan*/ ) ; 

int
cifs_alloc_hash(const char *name,
		struct crypto_shash **shash, struct sdesc **sdesc)
{
	int rc = 0;
	size_t size;

	if (*sdesc != NULL)
		return 0;

	*shash = crypto_alloc_shash(name, 0, 0);
	if (IS_ERR(*shash)) {
		cifs_dbg(VFS, "could not allocate crypto %s\n", name);
		rc = PTR_ERR(*shash);
		*shash = NULL;
		*sdesc = NULL;
		return rc;
	}

	size = sizeof(struct shash_desc) + crypto_shash_descsize(*shash);
	*sdesc = kmalloc(size, GFP_KERNEL);
	if (*sdesc == NULL) {
		cifs_dbg(VFS, "no memory left to allocate crypto %s\n", name);
		crypto_free_shash(*shash);
		*shash = NULL;
		return -ENOMEM;
	}

	(*sdesc)->shash.tfm = *shash;
	return 0;
}