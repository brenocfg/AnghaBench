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
struct nvmet_ns {int /*<<< orphan*/ * file; int /*<<< orphan*/ * bvec_cache; int /*<<< orphan*/ * bvec_pool; scalar_t__ buffered_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffered_io_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 

void nvmet_file_ns_disable(struct nvmet_ns *ns)
{
	if (ns->file) {
		if (ns->buffered_io)
			flush_workqueue(buffered_io_wq);
		mempool_destroy(ns->bvec_pool);
		ns->bvec_pool = NULL;
		kmem_cache_destroy(ns->bvec_cache);
		ns->bvec_cache = NULL;
		fput(ns->file);
		ns->file = NULL;
	}
}