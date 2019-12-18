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
struct insn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  insn_init (struct insn*,void const*,int,int) ; 

__attribute__((used)) static inline void kernel_insn_init(struct insn *insn,
				    const void *kaddr, int buf_len)
{
#ifdef CONFIG_X86_64
	insn_init(insn, kaddr, buf_len, 1);
#else /* CONFIG_X86_32 */
	insn_init(insn, kaddr, buf_len, 0);
#endif
}