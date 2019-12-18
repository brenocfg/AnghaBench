#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bpf_verifier_env {int subprog_cnt; TYPE_4__* subprog_info; TYPE_3__* prog; } ;
struct TYPE_8__ {int /*<<< orphan*/  start; } ;
struct TYPE_7__ {TYPE_2__* aux; } ;
struct TYPE_6__ {TYPE_1__* func_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  insn_off; } ;

/* Variables and functions */

__attribute__((used)) static void adjust_btf_func(struct bpf_verifier_env *env)
{
	int i;

	if (!env->prog->aux->func_info)
		return;

	for (i = 0; i < env->subprog_cnt; i++)
		env->prog->aux->func_info[i].insn_off = env->subprog_info[i].start;
}