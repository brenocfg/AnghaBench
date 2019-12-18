#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct crypto_comp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bufsize; } ;
struct TYPE_3__ {int name; int (* zbufsize ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PSTORE_COMPRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (struct crypto_comp*) ; 
 int PTR_ERR (struct crypto_comp*) ; 
 char* big_oops_buf ; 
 int big_oops_buf_sz ; 
 struct crypto_comp* crypto_alloc_comp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_has_comp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 TYPE_2__* psinfo ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 struct crypto_comp* tfm ; 
 TYPE_1__* zbackend ; 

__attribute__((used)) static void allocate_buf_for_compression(void)
{
	struct crypto_comp *ctx;
	int size;
	char *buf;

	/* Skip if not built-in or compression backend not selected yet. */
	if (!IS_ENABLED(CONFIG_PSTORE_COMPRESS) || !zbackend)
		return;

	/* Skip if no pstore backend yet or compression init already done. */
	if (!psinfo || tfm)
		return;

	if (!crypto_has_comp(zbackend->name, 0, 0)) {
		pr_err("Unknown compression: %s\n", zbackend->name);
		return;
	}

	size = zbackend->zbufsize(psinfo->bufsize);
	if (size <= 0) {
		pr_err("Invalid compression size for %s: %d\n",
		       zbackend->name, size);
		return;
	}

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf) {
		pr_err("Failed %d byte compression buffer allocation for: %s\n",
		       size, zbackend->name);
		return;
	}

	ctx = crypto_alloc_comp(zbackend->name, 0, 0);
	if (IS_ERR_OR_NULL(ctx)) {
		kfree(buf);
		pr_err("crypto_alloc_comp('%s') failed: %ld\n", zbackend->name,
		       PTR_ERR(ctx));
		return;
	}

	/* A non-NULL big_oops_buf indicates compression is available. */
	tfm = ctx;
	big_oops_buf_sz = size;
	big_oops_buf = buf;

	pr_info("Using crash dump compression: %s\n", zbackend->name);
}