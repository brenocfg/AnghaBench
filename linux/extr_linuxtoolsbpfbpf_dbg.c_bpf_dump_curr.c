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
struct sock_filter {int jt; int jf; int /*<<< orphan*/  k; int /*<<< orphan*/  code; } ;
struct bpf_regs {int Pc; scalar_t__* M; int /*<<< orphan*/  R; scalar_t__ Rs; int /*<<< orphan*/  X; int /*<<< orphan*/  A; } ;

/* Variables and functions */
 int BPF_MEMWORDS ; 
 int /*<<< orphan*/  bpf_disasm (struct sock_filter,int) ; 
 int /*<<< orphan*/  rl_printf (char*,...) ; 

__attribute__((used)) static void bpf_dump_curr(struct bpf_regs *r, struct sock_filter *f)
{
	int i, m = 0;

	rl_printf("pc:       [%u]\n", r->Pc);
	rl_printf("code:     [%u] jt[%u] jf[%u] k[%u]\n",
		  f->code, f->jt, f->jf, f->k);
	rl_printf("curr:     ");
	bpf_disasm(*f, r->Pc);

	if (f->jt || f->jf) {
		rl_printf("jt:       ");
		bpf_disasm(*(f + f->jt + 1), r->Pc + f->jt + 1);
		rl_printf("jf:       ");
		bpf_disasm(*(f + f->jf + 1), r->Pc + f->jf + 1);
	}

	rl_printf("A:        [%#08x][%u]\n", r->A, r->A);
	rl_printf("X:        [%#08x][%u]\n", r->X, r->X);
	if (r->Rs)
		rl_printf("ret:      [%#08x][%u]!\n", r->R, r->R);

	for (i = 0; i < BPF_MEMWORDS; i++) {
		if (r->M[i]) {
			m++;
			rl_printf("M[%d]: [%#08x][%u]\n", i, r->M[i], r->M[i]);
		}
	}
	if (m == 0)
		rl_printf("M[0,%d]:  [%#08x][%u]\n", BPF_MEMWORDS - 1, 0, 0);
}