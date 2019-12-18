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
struct pt_regs {int dummy; } ;
struct bpf_raw_tp_regs {struct pt_regs* regs; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pt_regs*) ; 
 int /*<<< orphan*/  EBUSY ; 
 struct pt_regs* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bpf_raw_tp_nest_level ; 
 int /*<<< orphan*/  bpf_raw_tp_regs ; 
 int /*<<< orphan*/  this_cpu_dec (int /*<<< orphan*/ ) ; 
 int this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 struct bpf_raw_tp_regs* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pt_regs *get_bpf_raw_tp_regs(void)
{
	struct bpf_raw_tp_regs *tp_regs = this_cpu_ptr(&bpf_raw_tp_regs);
	int nest_level = this_cpu_inc_return(bpf_raw_tp_nest_level);

	if (WARN_ON_ONCE(nest_level > ARRAY_SIZE(tp_regs->regs))) {
		this_cpu_dec(bpf_raw_tp_nest_level);
		return ERR_PTR(-EBUSY);
	}

	return &tp_regs->regs[nest_level - 1];
}