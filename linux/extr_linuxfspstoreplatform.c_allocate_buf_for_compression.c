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
struct TYPE_4__ {int /*<<< orphan*/  bufsize; } ;
struct TYPE_3__ {scalar_t__ (* zbufsize ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PSTORE_COMPRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * big_oops_buf ; 
 scalar_t__ big_oops_buf_sz ; 
 int /*<<< orphan*/  crypto_alloc_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_has_comp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 TYPE_2__* psinfo ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tfm ; 
 TYPE_1__* zbackend ; 

__attribute__((used)) static void allocate_buf_for_compression(void)
{
	if (!IS_ENABLED(CONFIG_PSTORE_COMPRESS) || !zbackend)
		return;

	if (!crypto_has_comp(zbackend->name, 0, 0)) {
		pr_err("No %s compression\n", zbackend->name);
		return;
	}

	big_oops_buf_sz = zbackend->zbufsize(psinfo->bufsize);
	if (big_oops_buf_sz <= 0)
		return;

	big_oops_buf = kmalloc(big_oops_buf_sz, GFP_KERNEL);
	if (!big_oops_buf) {
		pr_err("allocate compression buffer error!\n");
		return;
	}

	tfm = crypto_alloc_comp(zbackend->name, 0, 0);
	if (IS_ERR_OR_NULL(tfm)) {
		kfree(big_oops_buf);
		big_oops_buf = NULL;
		pr_err("crypto_alloc_comp() failed!\n");
		return;
	}
}