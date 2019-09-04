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
struct xdp_frame {size_t len; struct virtio_net_hdr* data; } ;
struct virtio_net_hdr {int /*<<< orphan*/  member_0; } ;
struct tun_struct {int flags; int /*<<< orphan*/  pcpu_stats; int /*<<< orphan*/  vnet_hdr_sz; } ;
struct tun_pcpu_stats {size_t tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct tun_file {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  gso ;

/* Variables and functions */
 size_t EFAULT ; 
 size_t EINVAL ; 
 int IFF_VNET_HDR ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int copy_to_iter (struct virtio_net_hdr*,size_t,struct iov_iter*) ; 
 struct tun_pcpu_stats* get_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iov_iter_advance (struct iov_iter*,int) ; 
 int iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  put_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t tun_put_user_xdp(struct tun_struct *tun,
				struct tun_file *tfile,
				struct xdp_frame *xdp_frame,
				struct iov_iter *iter)
{
	int vnet_hdr_sz = 0;
	size_t size = xdp_frame->len;
	struct tun_pcpu_stats *stats;
	size_t ret;

	if (tun->flags & IFF_VNET_HDR) {
		struct virtio_net_hdr gso = { 0 };

		vnet_hdr_sz = READ_ONCE(tun->vnet_hdr_sz);
		if (unlikely(iov_iter_count(iter) < vnet_hdr_sz))
			return -EINVAL;
		if (unlikely(copy_to_iter(&gso, sizeof(gso), iter) !=
			     sizeof(gso)))
			return -EFAULT;
		iov_iter_advance(iter, vnet_hdr_sz - sizeof(gso));
	}

	ret = copy_to_iter(xdp_frame->data, size, iter) + vnet_hdr_sz;

	stats = get_cpu_ptr(tun->pcpu_stats);
	u64_stats_update_begin(&stats->syncp);
	stats->tx_packets++;
	stats->tx_bytes += ret;
	u64_stats_update_end(&stats->syncp);
	put_cpu_ptr(tun->pcpu_stats);

	return ret;
}