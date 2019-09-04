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
struct TYPE_2__ {scalar_t__ bufsize; int /*<<< orphan*/  buf; } ;
struct ramoops_context {int /*<<< orphan*/  cprz; int /*<<< orphan*/  mprz; TYPE_1__ pstore; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct ramoops_context oops_cxt ; 
 int /*<<< orphan*/  persistent_ram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstore_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  ramoops_free_przs (struct ramoops_context*) ; 

__attribute__((used)) static int ramoops_remove(struct platform_device *pdev)
{
	struct ramoops_context *cxt = &oops_cxt;

	pstore_unregister(&cxt->pstore);

	kfree(cxt->pstore.buf);
	cxt->pstore.bufsize = 0;

	persistent_ram_free(cxt->mprz);
	persistent_ram_free(cxt->cprz);
	ramoops_free_przs(cxt);

	return 0;
}