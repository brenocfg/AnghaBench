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
struct path {TYPE_1__* dentry; } ;
struct ns_get_path_bpf_map_args {struct bpf_map_info* info; int /*<<< orphan*/  offmap; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_2__* i_sb; } ;
struct bpf_map_info {int /*<<< orphan*/  netns_ino; int /*<<< orphan*/  netns_dev; int /*<<< orphan*/  ifindex; } ;
struct bpf_map {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_dev; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  bpf_map_offload_info_fill_ns ; 
 int /*<<< orphan*/  map_to_offmap (struct bpf_map*) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 void* ns_get_path_cb (struct path*,int /*<<< orphan*/ ,struct ns_get_path_bpf_map_args*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 

int bpf_map_offload_info_fill(struct bpf_map_info *info, struct bpf_map *map)
{
	struct ns_get_path_bpf_map_args args = {
		.offmap	= map_to_offmap(map),
		.info	= info,
	};
	struct inode *ns_inode;
	struct path ns_path;
	void *res;

	res = ns_get_path_cb(&ns_path, bpf_map_offload_info_fill_ns, &args);
	if (IS_ERR(res)) {
		if (!info->ifindex)
			return -ENODEV;
		return PTR_ERR(res);
	}

	ns_inode = ns_path.dentry->d_inode;
	info->netns_dev = new_encode_dev(ns_inode->i_sb->s_dev);
	info->netns_ino = ns_inode->i_ino;
	path_put(&ns_path);

	return 0;
}