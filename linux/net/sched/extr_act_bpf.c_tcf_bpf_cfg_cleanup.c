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
struct tcf_bpf_cfg {int /*<<< orphan*/  bpf_name; int /*<<< orphan*/  bpf_ops; scalar_t__ is_ebpf; struct bpf_prog* filter; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_prog_destroy (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcf_bpf_cfg_cleanup(const struct tcf_bpf_cfg *cfg)
{
	struct bpf_prog *filter = cfg->filter;

	if (filter) {
		if (cfg->is_ebpf)
			bpf_prog_put(filter);
		else
			bpf_prog_destroy(filter);
	}

	kfree(cfg->bpf_ops);
	kfree(cfg->bpf_name);
}