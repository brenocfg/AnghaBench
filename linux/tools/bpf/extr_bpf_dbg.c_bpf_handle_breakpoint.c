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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sock_filter {int dummy; } ;
struct bpf_regs {size_t Pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_dump_curr (struct bpf_regs*,struct sock_filter*) ; 
 int /*<<< orphan*/  bpf_dump_pkt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rl_printf (char*) ; 

__attribute__((used)) static bool bpf_handle_breakpoint(struct bpf_regs *r, struct sock_filter *f,
				  uint8_t *pkt, uint32_t pkt_caplen,
				  uint32_t pkt_len)
{
	rl_printf("-- register dump --\n");
	bpf_dump_curr(r, &f[r->Pc]);
	rl_printf("-- packet dump --\n");
	bpf_dump_pkt(pkt, pkt_caplen, pkt_len);
	rl_printf("(breakpoint)\n");
	return true;
}