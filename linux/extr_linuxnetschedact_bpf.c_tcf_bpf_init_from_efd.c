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
typedef  int /*<<< orphan*/  u32 ;
struct tcf_bpf_cfg {char* bpf_name; int is_ebpf; struct bpf_prog* filter; } ;
struct nlattr {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SCHED_ACT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int PTR_ERR (struct bpf_prog*) ; 
 size_t TCA_ACT_BPF_FD ; 
 size_t TCA_ACT_BPF_NAME ; 
 struct bpf_prog* bpf_prog_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 char* nla_memdup (struct nlattr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tcf_bpf_init_from_efd(struct nlattr **tb, struct tcf_bpf_cfg *cfg)
{
	struct bpf_prog *fp;
	char *name = NULL;
	u32 bpf_fd;

	bpf_fd = nla_get_u32(tb[TCA_ACT_BPF_FD]);

	fp = bpf_prog_get_type(bpf_fd, BPF_PROG_TYPE_SCHED_ACT);
	if (IS_ERR(fp))
		return PTR_ERR(fp);

	if (tb[TCA_ACT_BPF_NAME]) {
		name = nla_memdup(tb[TCA_ACT_BPF_NAME], GFP_KERNEL);
		if (!name) {
			bpf_prog_put(fp);
			return -ENOMEM;
		}
	}

	cfg->bpf_name = name;
	cfg->filter = fp;
	cfg->is_ebpf = true;

	return 0;
}