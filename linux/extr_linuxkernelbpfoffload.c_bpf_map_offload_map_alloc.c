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
union bpf_attr {scalar_t__ map_type; int /*<<< orphan*/  map_ifindex; } ;
struct net {int dummy; } ;
struct bpf_map {int dummy; } ;
struct bpf_offloaded_map {struct bpf_map map; int /*<<< orphan*/  offloads; int /*<<< orphan*/  netdev; } ;
struct bpf_offload_netdev {int /*<<< orphan*/  maps; } ;
struct TYPE_4__ {TYPE_1__* nsproxy; } ;
struct TYPE_3__ {struct net* net_ns; } ;

/* Variables and functions */
 scalar_t__ BPF_MAP_TYPE_ARRAY ; 
 scalar_t__ BPF_MAP_TYPE_HASH ; 
 int /*<<< orphan*/  BPF_OFFLOAD_MAP_ALLOC ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_USER ; 
 int /*<<< orphan*/  __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int bpf_dev_offload_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_devs_lock ; 
 int /*<<< orphan*/  bpf_map_init_from_attr (struct bpf_map*,union bpf_attr*) ; 
 int bpf_map_offload_ndo (struct bpf_offloaded_map*,int /*<<< orphan*/ ) ; 
 struct bpf_offload_netdev* bpf_offload_find_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bpf_offloaded_map*) ; 
 struct bpf_offloaded_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

struct bpf_map *bpf_map_offload_map_alloc(union bpf_attr *attr)
{
	struct net *net = current->nsproxy->net_ns;
	struct bpf_offload_netdev *ondev;
	struct bpf_offloaded_map *offmap;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return ERR_PTR(-EPERM);
	if (attr->map_type != BPF_MAP_TYPE_ARRAY &&
	    attr->map_type != BPF_MAP_TYPE_HASH)
		return ERR_PTR(-EINVAL);

	offmap = kzalloc(sizeof(*offmap), GFP_USER);
	if (!offmap)
		return ERR_PTR(-ENOMEM);

	bpf_map_init_from_attr(&offmap->map, attr);

	rtnl_lock();
	down_write(&bpf_devs_lock);
	offmap->netdev = __dev_get_by_index(net, attr->map_ifindex);
	err = bpf_dev_offload_check(offmap->netdev);
	if (err)
		goto err_unlock;

	ondev = bpf_offload_find_netdev(offmap->netdev);
	if (!ondev) {
		err = -EINVAL;
		goto err_unlock;
	}

	err = bpf_map_offload_ndo(offmap, BPF_OFFLOAD_MAP_ALLOC);
	if (err)
		goto err_unlock;

	list_add_tail(&offmap->offloads, &ondev->maps);
	up_write(&bpf_devs_lock);
	rtnl_unlock();

	return &offmap->map;

err_unlock:
	up_write(&bpf_devs_lock);
	rtnl_unlock();
	kfree(offmap);
	return ERR_PTR(err);
}