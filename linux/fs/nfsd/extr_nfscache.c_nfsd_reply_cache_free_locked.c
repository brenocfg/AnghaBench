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
struct TYPE_2__ {scalar_t__ iov_base; scalar_t__ iov_len; } ;
struct svc_cacherep {scalar_t__ c_type; scalar_t__ c_state; int /*<<< orphan*/  c_lru; int /*<<< orphan*/  c_node; TYPE_1__ c_replvec; } ;
struct nfsd_net {int drc_mem_usage; int /*<<< orphan*/  drc_slab; int /*<<< orphan*/  num_drc_entries; } ;
struct nfsd_drc_bucket {int /*<<< orphan*/  rb_head; } ;

/* Variables and functions */
 scalar_t__ RC_REPLBUFF ; 
 scalar_t__ RC_UNUSED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct svc_cacherep*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfsd_reply_cache_free_locked(struct nfsd_drc_bucket *b, struct svc_cacherep *rp,
				struct nfsd_net *nn)
{
	if (rp->c_type == RC_REPLBUFF && rp->c_replvec.iov_base) {
		nn->drc_mem_usage -= rp->c_replvec.iov_len;
		kfree(rp->c_replvec.iov_base);
	}
	if (rp->c_state != RC_UNUSED) {
		rb_erase(&rp->c_node, &b->rb_head);
		list_del(&rp->c_lru);
		atomic_dec(&nn->num_drc_entries);
		nn->drc_mem_usage -= sizeof(*rp);
	}
	kmem_cache_free(nn->drc_slab, rp);
}