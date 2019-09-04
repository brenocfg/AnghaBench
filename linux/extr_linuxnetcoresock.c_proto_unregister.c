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
struct proto {TYPE_1__* twsk_prot; int /*<<< orphan*/  rsk_prot; int /*<<< orphan*/ * slab; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/ * twsk_slab; int /*<<< orphan*/  twsk_slab_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proto_list_mutex ; 
 int /*<<< orphan*/  release_proto_idx (struct proto*) ; 
 int /*<<< orphan*/  req_prot_cleanup (int /*<<< orphan*/ ) ; 

void proto_unregister(struct proto *prot)
{
	mutex_lock(&proto_list_mutex);
	release_proto_idx(prot);
	list_del(&prot->node);
	mutex_unlock(&proto_list_mutex);

	kmem_cache_destroy(prot->slab);
	prot->slab = NULL;

	req_prot_cleanup(prot->rsk_prot);

	if (prot->twsk_prot != NULL && prot->twsk_prot->twsk_slab != NULL) {
		kmem_cache_destroy(prot->twsk_prot->twsk_slab);
		kfree(prot->twsk_prot->twsk_slab_name);
		prot->twsk_prot->twsk_slab = NULL;
	}
}