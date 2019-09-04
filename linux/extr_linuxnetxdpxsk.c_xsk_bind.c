#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct xdp_sock {scalar_t__ queue_id; int /*<<< orphan*/  mutex; TYPE_1__* umem; scalar_t__ tx; scalar_t__ rx; int /*<<< orphan*/  zc; struct net_device* dev; } ;
struct socket {struct sock* sk; } ;
struct sockaddr_xdp {scalar_t__ sxdp_family; scalar_t__ sxdp_queue_id; scalar_t__ sxdp_flags; int /*<<< orphan*/  sxdp_shared_umem_fd; int /*<<< orphan*/  sxdp_ifindex; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {scalar_t__ real_num_rx_queues; scalar_t__ real_num_tx_queues; } ;
struct TYPE_5__ {int /*<<< orphan*/  props; int /*<<< orphan*/  zc; scalar_t__ cq; scalar_t__ fq; } ;

/* Variables and functions */
 scalar_t__ AF_XDP ; 
 int EBADF ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct socket*) ; 
 int PTR_ERR (struct socket*) ; 
 scalar_t__ XDP_COPY ; 
 scalar_t__ XDP_SHARED_UMEM ; 
 scalar_t__ XDP_ZEROCOPY ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 
 int /*<<< orphan*/  xdp_add_sk_umem (TYPE_1__*,struct xdp_sock*) ; 
 int /*<<< orphan*/  xdp_get_umem (TYPE_1__*) ; 
 struct xdp_sock* xdp_sk (struct sock*) ; 
 int xdp_umem_assign_dev (TYPE_1__*,struct net_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xdp_umem_validate_queues (TYPE_1__*) ; 
 struct socket* xsk_lookup_xsk_from_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xskq_set_umem (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xsk_bind(struct socket *sock, struct sockaddr *addr, int addr_len)
{
	struct sockaddr_xdp *sxdp = (struct sockaddr_xdp *)addr;
	struct sock *sk = sock->sk;
	struct xdp_sock *xs = xdp_sk(sk);
	struct net_device *dev;
	u32 flags, qid;
	int err = 0;

	if (addr_len < sizeof(struct sockaddr_xdp))
		return -EINVAL;
	if (sxdp->sxdp_family != AF_XDP)
		return -EINVAL;

	mutex_lock(&xs->mutex);
	if (xs->dev) {
		err = -EBUSY;
		goto out_release;
	}

	dev = dev_get_by_index(sock_net(sk), sxdp->sxdp_ifindex);
	if (!dev) {
		err = -ENODEV;
		goto out_release;
	}

	if (!xs->rx && !xs->tx) {
		err = -EINVAL;
		goto out_unlock;
	}

	qid = sxdp->sxdp_queue_id;

	if ((xs->rx && qid >= dev->real_num_rx_queues) ||
	    (xs->tx && qid >= dev->real_num_tx_queues)) {
		err = -EINVAL;
		goto out_unlock;
	}

	flags = sxdp->sxdp_flags;

	if (flags & XDP_SHARED_UMEM) {
		struct xdp_sock *umem_xs;
		struct socket *sock;

		if ((flags & XDP_COPY) || (flags & XDP_ZEROCOPY)) {
			/* Cannot specify flags for shared sockets. */
			err = -EINVAL;
			goto out_unlock;
		}

		if (xs->umem) {
			/* We have already our own. */
			err = -EINVAL;
			goto out_unlock;
		}

		sock = xsk_lookup_xsk_from_fd(sxdp->sxdp_shared_umem_fd);
		if (IS_ERR(sock)) {
			err = PTR_ERR(sock);
			goto out_unlock;
		}

		umem_xs = xdp_sk(sock->sk);
		if (!umem_xs->umem) {
			/* No umem to inherit. */
			err = -EBADF;
			sockfd_put(sock);
			goto out_unlock;
		} else if (umem_xs->dev != dev || umem_xs->queue_id != qid) {
			err = -EINVAL;
			sockfd_put(sock);
			goto out_unlock;
		}

		xdp_get_umem(umem_xs->umem);
		xs->umem = umem_xs->umem;
		sockfd_put(sock);
	} else if (!xs->umem || !xdp_umem_validate_queues(xs->umem)) {
		err = -EINVAL;
		goto out_unlock;
	} else {
		/* This xsk has its own umem. */
		xskq_set_umem(xs->umem->fq, &xs->umem->props);
		xskq_set_umem(xs->umem->cq, &xs->umem->props);

		err = xdp_umem_assign_dev(xs->umem, dev, qid, flags);
		if (err)
			goto out_unlock;
	}

	xs->dev = dev;
	xs->zc = xs->umem->zc;
	xs->queue_id = qid;
	xskq_set_umem(xs->rx, &xs->umem->props);
	xskq_set_umem(xs->tx, &xs->umem->props);
	xdp_add_sk_umem(xs->umem, xs);

out_unlock:
	if (err)
		dev_put(dev);
out_release:
	mutex_unlock(&xs->mutex);
	return err;
}