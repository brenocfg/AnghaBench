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
struct sock_filter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_disasm (struct sock_filter const,unsigned int) ; 

__attribute__((used)) static void bpf_disasm_all(const struct sock_filter *f, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		bpf_disasm(f[i], i);
}