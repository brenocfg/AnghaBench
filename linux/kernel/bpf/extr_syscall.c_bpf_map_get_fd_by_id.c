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
union bpf_attr {int open_flags; int /*<<< orphan*/  map_id; } ;
typedef  int /*<<< orphan*/  u32 ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_GET_FD_BY_ID ; 
 int BPF_OBJ_FLAG_MASK ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ CHECK_ATTR (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int EPERM ; 
 struct bpf_map* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 int PTR_ERR (struct bpf_map*) ; 
 struct bpf_map* __bpf_map_inc_not_zero (struct bpf_map*,int) ; 
 int bpf_get_file_flag (int) ; 
 int bpf_map_new_fd (struct bpf_map*,int) ; 
 int /*<<< orphan*/  bpf_map_put_with_uref (struct bpf_map*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct bpf_map* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_idr ; 
 int /*<<< orphan*/  map_idr_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_map_get_fd_by_id(const union bpf_attr *attr)
{
	struct bpf_map *map;
	u32 id = attr->map_id;
	int f_flags;
	int fd;

	if (CHECK_ATTR(BPF_MAP_GET_FD_BY_ID) ||
	    attr->open_flags & ~BPF_OBJ_FLAG_MASK)
		return -EINVAL;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	f_flags = bpf_get_file_flag(attr->open_flags);
	if (f_flags < 0)
		return f_flags;

	spin_lock_bh(&map_idr_lock);
	map = idr_find(&map_idr, id);
	if (map)
		map = __bpf_map_inc_not_zero(map, true);
	else
		map = ERR_PTR(-ENOENT);
	spin_unlock_bh(&map_idr_lock);

	if (IS_ERR(map))
		return PTR_ERR(map);

	fd = bpf_map_new_fd(map, f_flags);
	if (fd < 0)
		bpf_map_put_with_uref(map);

	return fd;
}