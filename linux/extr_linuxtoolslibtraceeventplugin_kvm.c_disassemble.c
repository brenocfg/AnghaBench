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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static const char *disassemble(unsigned char *insn, int len, uint64_t rip,
			       int cr0_pe, int eflags_vm,
			       int cs_d, int cs_l)
{
	static char out[15*3+1];
	int i;

	for (i = 0; i < len; ++i)
		sprintf(out + i * 3, "%02x ", insn[i]);
	out[len*3-1] = '\0';
	return out;
}