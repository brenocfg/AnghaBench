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
struct xsk_socket {int prog_fd; int xsks_map_fd; } ;
struct bpf_prog_info {size_t nr_map_ids; int /*<<< orphan*/  name; scalar_t__ map_ids; } ;
struct bpf_map_info {size_t nr_map_ids; int /*<<< orphan*/  name; scalar_t__ map_ids; } ;
typedef  scalar_t__ __u64 ;
typedef  size_t __u32 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int bpf_map_get_fd_by_id (size_t) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,size_t*) ; 
 size_t* calloc (size_t,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 int /*<<< orphan*/  memset (struct bpf_prog_info*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xsk_lookup_bpf_maps(struct xsk_socket *xsk)
{
	__u32 i, *map_ids, num_maps, prog_len = sizeof(struct bpf_prog_info);
	__u32 map_len = sizeof(struct bpf_map_info);
	struct bpf_prog_info prog_info = {};
	struct bpf_map_info map_info;
	int fd, err;

	err = bpf_obj_get_info_by_fd(xsk->prog_fd, &prog_info, &prog_len);
	if (err)
		return err;

	num_maps = prog_info.nr_map_ids;

	map_ids = calloc(prog_info.nr_map_ids, sizeof(*map_ids));
	if (!map_ids)
		return -ENOMEM;

	memset(&prog_info, 0, prog_len);
	prog_info.nr_map_ids = num_maps;
	prog_info.map_ids = (__u64)(unsigned long)map_ids;

	err = bpf_obj_get_info_by_fd(xsk->prog_fd, &prog_info, &prog_len);
	if (err)
		goto out_map_ids;

	xsk->xsks_map_fd = -1;

	for (i = 0; i < prog_info.nr_map_ids; i++) {
		fd = bpf_map_get_fd_by_id(map_ids[i]);
		if (fd < 0)
			continue;

		err = bpf_obj_get_info_by_fd(fd, &map_info, &map_len);
		if (err) {
			close(fd);
			continue;
		}

		if (!strcmp(map_info.name, "xsks_map")) {
			xsk->xsks_map_fd = fd;
			continue;
		}

		close(fd);
	}

	err = 0;
	if (xsk->xsks_map_fd == -1)
		err = -ENOENT;

out_map_ids:
	free(map_ids);
	return err;
}