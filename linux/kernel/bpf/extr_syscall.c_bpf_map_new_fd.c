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
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPEN_FMODE (int) ; 
 int O_CLOEXEC ; 
 int anon_inode_getfd (char*,int /*<<< orphan*/ *,struct bpf_map*,int) ; 
 int /*<<< orphan*/  bpf_map_fops ; 
 int security_bpf_map (struct bpf_map*,int /*<<< orphan*/ ) ; 

int bpf_map_new_fd(struct bpf_map *map, int flags)
{
	int ret;

	ret = security_bpf_map(map, OPEN_FMODE(flags));
	if (ret < 0)
		return ret;

	return anon_inode_getfd("bpf-map", &bpf_map_fops, map,
				flags | O_CLOEXEC);
}