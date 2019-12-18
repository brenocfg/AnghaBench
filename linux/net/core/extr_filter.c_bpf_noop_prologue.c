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
struct bpf_prog {int dummy; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int bpf_noop_prologue(struct bpf_insn *insn_buf, bool direct_write,
			     const struct bpf_prog *prog)
{
	/* Neither direct read nor direct write requires any preliminary
	 * action.
	 */
	return 0;
}