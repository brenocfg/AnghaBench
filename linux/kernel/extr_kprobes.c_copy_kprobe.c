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
struct kprobe {int /*<<< orphan*/  ainsn; int /*<<< orphan*/  opcode; } ;
struct arch_specific_insn {int dummy; } ;
typedef  int /*<<< orphan*/  kprobe_opcode_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void copy_kprobe(struct kprobe *ap, struct kprobe *p)
{
	memcpy(&p->opcode, &ap->opcode, sizeof(kprobe_opcode_t));
	memcpy(&p->ainsn, &ap->ainsn, sizeof(struct arch_specific_insn));
}