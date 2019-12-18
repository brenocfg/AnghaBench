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
struct xdp_umem {scalar_t__ cq; scalar_t__ fq; int /*<<< orphan*/  users; scalar_t__ zc; int /*<<< orphan*/  queue_id; TYPE_1__* dev; scalar_t__ headroom; scalar_t__ chunk_size_nohr; int /*<<< orphan*/  npgs; int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
struct xdp_sock {struct xdp_umem* umem; } ;
struct xdp_diag_umem {int /*<<< orphan*/  refs; int /*<<< orphan*/  flags; int /*<<< orphan*/  queue_id; int /*<<< orphan*/  ifindex; scalar_t__ headroom; scalar_t__ chunk_size; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  size; int /*<<< orphan*/  id; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  du ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDP_DIAG_UMEM ; 
 int /*<<< orphan*/  XDP_DIAG_UMEM_COMPLETION_RING ; 
 int /*<<< orphan*/  XDP_DIAG_UMEM_FILL_RING ; 
 int /*<<< orphan*/  XDP_DU_F_ZEROCOPY ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct xdp_diag_umem*) ; 
 int /*<<< orphan*/  refcount_read (int /*<<< orphan*/ *) ; 
 int xsk_diag_put_ring (scalar_t__,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int xsk_diag_put_umem(const struct xdp_sock *xs, struct sk_buff *nlskb)
{
	struct xdp_umem *umem = xs->umem;
	struct xdp_diag_umem du = {};
	int err;

	if (!umem)
		return 0;

	du.id = umem->id;
	du.size = umem->size;
	du.num_pages = umem->npgs;
	du.chunk_size = umem->chunk_size_nohr + umem->headroom;
	du.headroom = umem->headroom;
	du.ifindex = umem->dev ? umem->dev->ifindex : 0;
	du.queue_id = umem->queue_id;
	du.flags = 0;
	if (umem->zc)
		du.flags |= XDP_DU_F_ZEROCOPY;
	du.refs = refcount_read(&umem->users);

	err = nla_put(nlskb, XDP_DIAG_UMEM, sizeof(du), &du);

	if (!err && umem->fq)
		err = xsk_diag_put_ring(umem->fq, XDP_DIAG_UMEM_FILL_RING, nlskb);
	if (!err && umem->cq) {
		err = xsk_diag_put_ring(umem->cq, XDP_DIAG_UMEM_COMPLETION_RING,
					nlskb);
	}
	return err;
}