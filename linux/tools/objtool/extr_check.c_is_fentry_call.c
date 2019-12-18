#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct instruction {scalar_t__ type; TYPE_1__* call_dest; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ INSN_CALL ; 
 scalar_t__ STT_NOTYPE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool is_fentry_call(struct instruction *insn)
{
	if (insn->type == INSN_CALL &&
	    insn->call_dest->type == STT_NOTYPE &&
	    !strcmp(insn->call_dest->name, "__fentry__"))
		return true;

	return false;
}