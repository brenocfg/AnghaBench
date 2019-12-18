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
struct tcf_bpf_cfg {int /*<<< orphan*/  bpf_name; int /*<<< orphan*/  bpf_ops; int /*<<< orphan*/  filter; int /*<<< orphan*/  is_ebpf; } ;
struct tcf_bpf {int /*<<< orphan*/  bpf_name; int /*<<< orphan*/  bpf_ops; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcf_bpf_is_ebpf (struct tcf_bpf const*) ; 

__attribute__((used)) static void tcf_bpf_prog_fill_cfg(const struct tcf_bpf *prog,
				  struct tcf_bpf_cfg *cfg)
{
	cfg->is_ebpf = tcf_bpf_is_ebpf(prog);
	/* updates to prog->filter are prevented, since it's called either
	 * with tcf lock or during final cleanup in rcu callback
	 */
	cfg->filter = rcu_dereference_protected(prog->filter, 1);

	cfg->bpf_ops = prog->bpf_ops;
	cfg->bpf_name = prog->bpf_name;
}