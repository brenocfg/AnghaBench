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
typedef  int /*<<< orphan*/  u32 ;
struct xdp_sock {int dummy; } ;
struct xdp_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_map {int map_type; } ;
struct bpf_dtab_netdev {int dummy; } ;
struct bpf_cpu_map_entry {int dummy; } ;

/* Variables and functions */
#define  BPF_MAP_TYPE_CPUMAP 131 
#define  BPF_MAP_TYPE_DEVMAP 130 
#define  BPF_MAP_TYPE_DEVMAP_HASH 129 
#define  BPF_MAP_TYPE_XSKMAP 128 
 int __xsk_map_redirect (struct bpf_map*,struct xdp_buff*,struct xdp_sock*) ; 
 int cpu_map_enqueue (struct bpf_cpu_map_entry*,struct xdp_buff*,struct net_device*) ; 
 int dev_map_enqueue (struct bpf_dtab_netdev*,struct xdp_buff*,struct net_device*) ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int __bpf_tx_xdp_map(struct net_device *dev_rx, void *fwd,
			    struct bpf_map *map,
			    struct xdp_buff *xdp,
			    u32 index)
{
	int err;

	switch (map->map_type) {
	case BPF_MAP_TYPE_DEVMAP:
	case BPF_MAP_TYPE_DEVMAP_HASH: {
		struct bpf_dtab_netdev *dst = fwd;

		err = dev_map_enqueue(dst, xdp, dev_rx);
		if (unlikely(err))
			return err;
		break;
	}
	case BPF_MAP_TYPE_CPUMAP: {
		struct bpf_cpu_map_entry *rcpu = fwd;

		err = cpu_map_enqueue(rcpu, xdp, dev_rx);
		if (unlikely(err))
			return err;
		break;
	}
	case BPF_MAP_TYPE_XSKMAP: {
		struct xdp_sock *xs = fwd;

		err = __xsk_map_redirect(map, xdp, xs);
		return err;
	}
	default:
		break;
	}
	return 0;
}