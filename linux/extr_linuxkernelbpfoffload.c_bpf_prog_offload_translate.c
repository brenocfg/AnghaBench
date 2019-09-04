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
struct TYPE_2__ {struct bpf_prog* prog; } ;
struct netdev_bpf {TYPE_1__ offload; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_OFFLOAD_TRANSLATE ; 
 int __bpf_offload_ndo (struct bpf_prog*,int /*<<< orphan*/ ,struct netdev_bpf*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int bpf_prog_offload_translate(struct bpf_prog *prog)
{
	struct netdev_bpf data = {};
	int ret;

	data.offload.prog = prog;

	rtnl_lock();
	ret = __bpf_offload_ndo(prog, BPF_OFFLOAD_TRANSLATE, &data);
	rtnl_unlock();

	return ret;
}