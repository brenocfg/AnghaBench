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
struct xsk_queue {int /*<<< orphan*/  ring; } ;
struct xdp_umem {int /*<<< orphan*/  cq; int /*<<< orphan*/  fq; } ;
struct xdp_sock {int /*<<< orphan*/  umem; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  state; } ;
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int /*<<< orphan*/  vm_page_prot; scalar_t__ vm_pgoff; } ;
struct socket {int /*<<< orphan*/  sk; } ;
struct page {int dummy; } ;
struct file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ PAGE_SHIFT ; 
 void* READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ XDP_PGOFF_RX_RING ; 
 scalar_t__ XDP_PGOFF_TX_RING ; 
 scalar_t__ XDP_UMEM_PGOFF_COMPLETION_RING ; 
 scalar_t__ XDP_UMEM_PGOFF_FILL_RING ; 
 void* XSK_READY ; 
 unsigned long page_size (struct page*) ; 
 int remap_pfn_range (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 struct page* virt_to_head_page (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (int /*<<< orphan*/ ) ; 
 struct xdp_sock* xdp_sk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsk_mmap(struct file *file, struct socket *sock,
		    struct vm_area_struct *vma)
{
	loff_t offset = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
	unsigned long size = vma->vm_end - vma->vm_start;
	struct xdp_sock *xs = xdp_sk(sock->sk);
	struct xsk_queue *q = NULL;
	struct xdp_umem *umem;
	unsigned long pfn;
	struct page *qpg;

	if (READ_ONCE(xs->state) != XSK_READY)
		return -EBUSY;

	if (offset == XDP_PGOFF_RX_RING) {
		q = READ_ONCE(xs->rx);
	} else if (offset == XDP_PGOFF_TX_RING) {
		q = READ_ONCE(xs->tx);
	} else {
		umem = READ_ONCE(xs->umem);
		if (!umem)
			return -EINVAL;

		/* Matches the smp_wmb() in XDP_UMEM_REG */
		smp_rmb();
		if (offset == XDP_UMEM_PGOFF_FILL_RING)
			q = READ_ONCE(umem->fq);
		else if (offset == XDP_UMEM_PGOFF_COMPLETION_RING)
			q = READ_ONCE(umem->cq);
	}

	if (!q)
		return -EINVAL;

	/* Matches the smp_wmb() in xsk_init_queue */
	smp_rmb();
	qpg = virt_to_head_page(q->ring);
	if (size > page_size(qpg))
		return -EINVAL;

	pfn = virt_to_phys(q->ring) >> PAGE_SHIFT;
	return remap_pfn_range(vma, vma->vm_start, pfn,
			       size, vma->vm_page_prot);
}