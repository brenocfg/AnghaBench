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
union bpf_attr {int /*<<< orphan*/  attach_flags; int /*<<< orphan*/  attach_type; int /*<<< orphan*/  target_fd; } ;
struct cgroup {int dummy; } ;
struct bpf_prog {int dummy; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct cgroup*) ; 
 int PTR_ERR (struct cgroup*) ; 
 int cgroup_bpf_attach (struct cgroup*,struct bpf_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cgroup* cgroup_get_from_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_put (struct cgroup*) ; 

int cgroup_bpf_prog_attach(const union bpf_attr *attr,
			   enum bpf_prog_type ptype, struct bpf_prog *prog)
{
	struct cgroup *cgrp;
	int ret;

	cgrp = cgroup_get_from_fd(attr->target_fd);
	if (IS_ERR(cgrp))
		return PTR_ERR(cgrp);

	ret = cgroup_bpf_attach(cgrp, prog, attr->attach_type,
				attr->attach_flags);
	cgroup_put(cgrp);
	return ret;
}