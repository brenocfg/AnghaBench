#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog_ops {int dummy; } ;
struct bpf_prog {int type; TYPE_1__* aux; } ;
typedef  enum bpf_prog_type { ____Placeholder_bpf_prog_type } bpf_prog_type ;
struct TYPE_2__ {struct bpf_prog_ops const* ops; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bpf_prog_ops**) ; 
 int EINVAL ; 
 int array_index_nospec (int,int) ; 
 struct bpf_prog_ops const bpf_offload_prog_ops ; 
 int /*<<< orphan*/  bpf_prog_is_dev_bound (TYPE_1__*) ; 
 struct bpf_prog_ops** bpf_prog_types ; 

__attribute__((used)) static int find_prog_type(enum bpf_prog_type type, struct bpf_prog *prog)
{
	const struct bpf_prog_ops *ops;

	if (type >= ARRAY_SIZE(bpf_prog_types))
		return -EINVAL;
	type = array_index_nospec(type, ARRAY_SIZE(bpf_prog_types));
	ops = bpf_prog_types[type];
	if (!ops)
		return -EINVAL;

	if (!bpf_prog_is_dev_bound(prog->aux))
		prog->aux->ops = ops;
	else
		prog->aux->ops = &bpf_offload_prog_ops;
	prog->type = type;
	return 0;
}