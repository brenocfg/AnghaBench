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
union bpf_attr {int target_fd; int /*<<< orphan*/  attach_type; } ;
struct fd {int dummy; } ;
struct bpf_prog {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 int PTR_ERR (struct bpf_map*) ; 
 struct bpf_map* __bpf_map_get (struct fd) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int sock_map_prog (struct bpf_map*,struct bpf_prog*,int /*<<< orphan*/ ) ; 

int sockmap_get_from_fd(const union bpf_attr *attr, int type,
			struct bpf_prog *prog)
{
	int ufd = attr->target_fd;
	struct bpf_map *map;
	struct fd f;
	int err;

	f = fdget(ufd);
	map = __bpf_map_get(f);
	if (IS_ERR(map))
		return PTR_ERR(map);

	err = sock_map_prog(map, prog, attr->attach_type);
	fdput(f);
	return err;
}