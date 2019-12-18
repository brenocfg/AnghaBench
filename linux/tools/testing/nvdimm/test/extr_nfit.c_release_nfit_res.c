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
struct TYPE_2__ {int /*<<< orphan*/  start; } ;
struct nfit_test_resource {int /*<<< orphan*/  buf; TYPE_1__ res; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ DIMM_SIZE ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct nfit_test_resource*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_pool ; 
 int /*<<< orphan*/  nfit_test_lock ; 
 scalar_t__ resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_nfit_res(void *data)
{
	struct nfit_test_resource *nfit_res = data;

	spin_lock(&nfit_test_lock);
	list_del(&nfit_res->list);
	spin_unlock(&nfit_test_lock);

	if (resource_size(&nfit_res->res) >= DIMM_SIZE)
		gen_pool_free(nfit_pool, nfit_res->res.start,
				resource_size(&nfit_res->res));
	vfree(nfit_res->buf);
	kfree(nfit_res);
}