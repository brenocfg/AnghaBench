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
struct ins_ops {int dummy; } ;
struct arm_annotate {int /*<<< orphan*/  jump_insn; int /*<<< orphan*/  call_insn; } ;
struct arch {struct arm_annotate* priv; } ;
typedef  int /*<<< orphan*/  regmatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  arch__associate_ins_ops (struct arch*,char const*,struct ins_ops*) ; 
 struct ins_ops call_ops ; 
 struct ins_ops jump_ops ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ins_ops *arm__associate_instruction_ops(struct arch *arch, const char *name)
{
	struct arm_annotate *arm = arch->priv;
	struct ins_ops *ops;
	regmatch_t match[2];

	if (!regexec(&arm->call_insn, name, 2, match, 0))
		ops = &call_ops;
	else if (!regexec(&arm->jump_insn, name, 2, match, 0))
		ops = &jump_ops;
	else
		return NULL;

	arch__associate_ins_ops(arch, name, ops);
	return ops;
}