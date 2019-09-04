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
typedef  int u16 ;
struct virtnet_info {int curr_queue_pairs; int xdp_queue_pairs; int max_queue_pairs; TYPE_2__* sq; TYPE_1__* rq; int /*<<< orphan*/  any_header_sg; scalar_t__ mergeable_rx_bufs; int /*<<< orphan*/  vdev; } ;
struct padded_vnet_hdr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {unsigned long mtu; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  vq; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; int /*<<< orphan*/  vq; int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PAGE_SIZE ; 
 int PTR_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CTRL_GUEST_OFFLOADS ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_CSUM ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_ECN ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_TSO4 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_TSO6 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_UFO ; 
 int _virtnet_set_queues (struct virtnet_info*,int) ; 
 struct bpf_prog* bpf_prog_add (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_sub (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct virtnet_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,int,...) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_rx_queues (struct net_device*,int) ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 scalar_t__ virtio_has_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtnet_clear_guest_offloads (struct virtnet_info*) ; 
 int /*<<< orphan*/  virtnet_napi_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtnet_napi_tx_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtnet_napi_tx_enable (struct virtnet_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtnet_restore_guest_offloads (struct virtnet_info*) ; 

__attribute__((used)) static int virtnet_xdp_set(struct net_device *dev, struct bpf_prog *prog,
			   struct netlink_ext_ack *extack)
{
	unsigned long int max_sz = PAGE_SIZE - sizeof(struct padded_vnet_hdr);
	struct virtnet_info *vi = netdev_priv(dev);
	struct bpf_prog *old_prog;
	u16 xdp_qp = 0, curr_qp;
	int i, err;

	if (!virtio_has_feature(vi->vdev, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS)
	    && (virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_TSO4) ||
	        virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_TSO6) ||
	        virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_ECN) ||
		virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_UFO) ||
		virtio_has_feature(vi->vdev, VIRTIO_NET_F_GUEST_CSUM))) {
		NL_SET_ERR_MSG_MOD(extack, "Can't set XDP while host is implementing LRO/CSUM, disable LRO/CSUM first");
		return -EOPNOTSUPP;
	}

	if (vi->mergeable_rx_bufs && !vi->any_header_sg) {
		NL_SET_ERR_MSG_MOD(extack, "XDP expects header/data in single page, any_header_sg required");
		return -EINVAL;
	}

	if (dev->mtu > max_sz) {
		NL_SET_ERR_MSG_MOD(extack, "MTU too large to enable XDP");
		netdev_warn(dev, "XDP requires MTU less than %lu\n", max_sz);
		return -EINVAL;
	}

	curr_qp = vi->curr_queue_pairs - vi->xdp_queue_pairs;
	if (prog)
		xdp_qp = nr_cpu_ids;

	/* XDP requires extra queues for XDP_TX */
	if (curr_qp + xdp_qp > vi->max_queue_pairs) {
		NL_SET_ERR_MSG_MOD(extack, "Too few free TX rings available");
		netdev_warn(dev, "request %i queues but max is %i\n",
			    curr_qp + xdp_qp, vi->max_queue_pairs);
		return -ENOMEM;
	}

	old_prog = rtnl_dereference(vi->rq[0].xdp_prog);
	if (!prog && !old_prog)
		return 0;

	if (prog) {
		prog = bpf_prog_add(prog, vi->max_queue_pairs - 1);
		if (IS_ERR(prog))
			return PTR_ERR(prog);
	}

	/* Make sure NAPI is not using any XDP TX queues for RX. */
	if (netif_running(dev)) {
		for (i = 0; i < vi->max_queue_pairs; i++) {
			napi_disable(&vi->rq[i].napi);
			virtnet_napi_tx_disable(&vi->sq[i].napi);
		}
	}

	if (!prog) {
		for (i = 0; i < vi->max_queue_pairs; i++) {
			rcu_assign_pointer(vi->rq[i].xdp_prog, prog);
			if (i == 0)
				virtnet_restore_guest_offloads(vi);
		}
		synchronize_net();
	}

	err = _virtnet_set_queues(vi, curr_qp + xdp_qp);
	if (err)
		goto err;
	netif_set_real_num_rx_queues(dev, curr_qp + xdp_qp);
	vi->xdp_queue_pairs = xdp_qp;

	if (prog) {
		for (i = 0; i < vi->max_queue_pairs; i++) {
			rcu_assign_pointer(vi->rq[i].xdp_prog, prog);
			if (i == 0 && !old_prog)
				virtnet_clear_guest_offloads(vi);
		}
	}

	for (i = 0; i < vi->max_queue_pairs; i++) {
		if (old_prog)
			bpf_prog_put(old_prog);
		if (netif_running(dev)) {
			virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
			virtnet_napi_tx_enable(vi, vi->sq[i].vq,
					       &vi->sq[i].napi);
		}
	}

	return 0;

err:
	if (!prog) {
		virtnet_clear_guest_offloads(vi);
		for (i = 0; i < vi->max_queue_pairs; i++)
			rcu_assign_pointer(vi->rq[i].xdp_prog, old_prog);
	}

	if (netif_running(dev)) {
		for (i = 0; i < vi->max_queue_pairs; i++) {
			virtnet_napi_enable(vi->rq[i].vq, &vi->rq[i].napi);
			virtnet_napi_tx_enable(vi, vi->sq[i].vq,
					       &vi->sq[i].napi);
		}
	}
	if (prog)
		bpf_prog_sub(prog, vi->max_queue_pairs - 1);
	return err;
}