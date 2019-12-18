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
struct bpf_prog_info {int nr_map_ids; int /*<<< orphan*/  map_ids; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int bpf_map_get_fd_by_id (int) ; 
 scalar_t__ bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 int bpf_prog_get_fd_by_id (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  log_err (char*,int) ; 

int get_map_fd_by_prog_id(int prog_id)
{
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	__u32 map_ids[1];
	int prog_fd = -1;
	int map_fd = -1;

	prog_fd = bpf_prog_get_fd_by_id(prog_id);
	if (prog_fd < 0) {
		log_err("Failed to get fd by prog id %d", prog_id);
		goto err;
	}

	info.nr_map_ids = 1;
	info.map_ids = (__u64) (unsigned long) map_ids;

	if (bpf_obj_get_info_by_fd(prog_fd, &info, &info_len)) {
		log_err("Failed to get info by prog fd %d", prog_fd);
		goto err;
	}

	if (!info.nr_map_ids) {
		log_err("No maps found for prog fd %d", prog_fd);
		goto err;
	}

	map_fd = bpf_map_get_fd_by_id(map_ids[0]);
	if (map_fd < 0)
		log_err("Failed to get fd by map id %d", map_ids[0]);
err:
	if (prog_fd >= 0)
		close(prog_fd);
	return map_fd;
}