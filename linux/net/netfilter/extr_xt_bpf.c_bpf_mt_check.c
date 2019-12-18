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
struct xt_mtchk_param {struct xt_bpf_info* matchinfo; } ;
struct xt_bpf_info {int /*<<< orphan*/  filter; int /*<<< orphan*/  bpf_program_num_elem; int /*<<< orphan*/  bpf_program; } ;

/* Variables and functions */
 int __bpf_mt_check_bytecode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bpf_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_bpf_info *info = par->matchinfo;

	return __bpf_mt_check_bytecode(info->bpf_program,
				       info->bpf_program_num_elem,
				       &info->filter);
}