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
struct insn {int x86_64; int opnd_bytes; int addr_bytes; void const* next_byte; void const* end_kaddr; void const* kaddr; } ;

/* Variables and functions */
 int MAX_INSN_SIZE ; 
 int /*<<< orphan*/  memset (struct insn*,int /*<<< orphan*/ ,int) ; 

void insn_init(struct insn *insn, const void *kaddr, int buf_len, int x86_64)
{
	/*
	 * Instructions longer than MAX_INSN_SIZE (15 bytes) are invalid
	 * even if the input buffer is long enough to hold them.
	 */
	if (buf_len > MAX_INSN_SIZE)
		buf_len = MAX_INSN_SIZE;

	memset(insn, 0, sizeof(*insn));
	insn->kaddr = kaddr;
	insn->end_kaddr = kaddr + buf_len;
	insn->next_byte = kaddr;
	insn->x86_64 = x86_64 ? 1 : 0;
	insn->opnd_bytes = 4;
	if (x86_64)
		insn->addr_bytes = 8;
	else
		insn->addr_bytes = 4;
}