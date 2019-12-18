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
struct proto {int slab_flags; int /*<<< orphan*/ * slab; int /*<<< orphan*/  rsk_prot; TYPE_1__* twsk_prot; int /*<<< orphan*/  node; int /*<<< orphan*/  name; int /*<<< orphan*/  usersize; int /*<<< orphan*/  useroffset; int /*<<< orphan*/  obj_size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * twsk_slab_name; int /*<<< orphan*/ * twsk_slab; int /*<<< orphan*/  twsk_obj_size; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SLAB_ACCOUNT ; 
 int SLAB_HWCACHE_ALIGN ; 
 int assign_proto_idx (struct proto*) ; 
 int /*<<< orphan*/ * kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_cache_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmem_cache_create_usercopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_list ; 
 int /*<<< orphan*/  proto_list_mutex ; 
 int /*<<< orphan*/  req_prot_cleanup (int /*<<< orphan*/ ) ; 
 scalar_t__ req_prot_init (struct proto*) ; 

int proto_register(struct proto *prot, int alloc_slab)
{
	int ret = -ENOBUFS;

	if (alloc_slab) {
		prot->slab = kmem_cache_create_usercopy(prot->name,
					prot->obj_size, 0,
					SLAB_HWCACHE_ALIGN | SLAB_ACCOUNT |
					prot->slab_flags,
					prot->useroffset, prot->usersize,
					NULL);

		if (prot->slab == NULL) {
			pr_crit("%s: Can't create sock SLAB cache!\n",
				prot->name);
			goto out;
		}

		if (req_prot_init(prot))
			goto out_free_request_sock_slab;

		if (prot->twsk_prot != NULL) {
			prot->twsk_prot->twsk_slab_name = kasprintf(GFP_KERNEL, "tw_sock_%s", prot->name);

			if (prot->twsk_prot->twsk_slab_name == NULL)
				goto out_free_request_sock_slab;

			prot->twsk_prot->twsk_slab =
				kmem_cache_create(prot->twsk_prot->twsk_slab_name,
						  prot->twsk_prot->twsk_obj_size,
						  0,
						  SLAB_ACCOUNT |
						  prot->slab_flags,
						  NULL);
			if (prot->twsk_prot->twsk_slab == NULL)
				goto out_free_timewait_sock_slab_name;
		}
	}

	mutex_lock(&proto_list_mutex);
	ret = assign_proto_idx(prot);
	if (ret) {
		mutex_unlock(&proto_list_mutex);
		goto out_free_timewait_sock_slab_name;
	}
	list_add(&prot->node, &proto_list);
	mutex_unlock(&proto_list_mutex);
	return ret;

out_free_timewait_sock_slab_name:
	if (alloc_slab && prot->twsk_prot)
		kfree(prot->twsk_prot->twsk_slab_name);
out_free_request_sock_slab:
	if (alloc_slab) {
		req_prot_cleanup(prot->rsk_prot);

		kmem_cache_destroy(prot->slab);
		prot->slab = NULL;
	}
out:
	return ret;
}