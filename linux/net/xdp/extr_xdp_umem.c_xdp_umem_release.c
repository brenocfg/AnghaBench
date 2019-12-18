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
struct xdp_umem {struct xdp_umem* pages; int /*<<< orphan*/ * cq; int /*<<< orphan*/ * fq; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xdp_umem*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  umem_ida ; 
 int /*<<< orphan*/  xdp_umem_clear_dev (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unaccount_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unmap_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unpin_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xsk_reuseq_destroy (struct xdp_umem*) ; 
 int /*<<< orphan*/  xskq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xdp_umem_release(struct xdp_umem *umem)
{
	rtnl_lock();
	xdp_umem_clear_dev(umem);
	rtnl_unlock();

	ida_simple_remove(&umem_ida, umem->id);

	if (umem->fq) {
		xskq_destroy(umem->fq);
		umem->fq = NULL;
	}

	if (umem->cq) {
		xskq_destroy(umem->cq);
		umem->cq = NULL;
	}

	xsk_reuseq_destroy(umem);

	xdp_umem_unmap_pages(umem);
	xdp_umem_unpin_pages(umem);

	kfree(umem->pages);
	umem->pages = NULL;

	xdp_umem_unaccount_pages(umem);
	kfree(umem);
}