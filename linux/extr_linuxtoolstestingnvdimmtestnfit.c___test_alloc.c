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
struct TYPE_4__ {char* name; void* end; void* start; } ;
struct nfit_test_resource {void* buf; int /*<<< orphan*/  list; int /*<<< orphan*/  requests; int /*<<< orphan*/  lock; TYPE_2__ res; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct nfit_test {int /*<<< orphan*/  resources; TYPE_1__ pdev; } ;
typedef  void* dma_addr_t ;

/* Variables and functions */
 size_t DIMM_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct nfit_test_resource*) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  kfree (struct nfit_test_resource*) ; 
 struct nfit_test_resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nfit_pool ; 
 int /*<<< orphan*/  nfit_test_lock ; 
 int /*<<< orphan*/  release_nfit_res ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void *__test_alloc(struct nfit_test *t, size_t size, dma_addr_t *dma,
		void *buf)
{
	struct device *dev = &t->pdev.dev;
	struct nfit_test_resource *nfit_res = kzalloc(sizeof(*nfit_res),
			GFP_KERNEL);
	int rc;

	if (!buf || !nfit_res || !*dma)
		goto err;
	rc = devm_add_action(dev, release_nfit_res, nfit_res);
	if (rc)
		goto err;
	INIT_LIST_HEAD(&nfit_res->list);
	memset(buf, 0, size);
	nfit_res->dev = dev;
	nfit_res->buf = buf;
	nfit_res->res.start = *dma;
	nfit_res->res.end = *dma + size - 1;
	nfit_res->res.name = "NFIT";
	spin_lock_init(&nfit_res->lock);
	INIT_LIST_HEAD(&nfit_res->requests);
	spin_lock(&nfit_test_lock);
	list_add(&nfit_res->list, &t->resources);
	spin_unlock(&nfit_test_lock);

	return nfit_res->buf;
 err:
	if (*dma && size >= DIMM_SIZE)
		gen_pool_free(nfit_pool, *dma, size);
	if (buf)
		vfree(buf);
	kfree(nfit_res);
	return NULL;
}