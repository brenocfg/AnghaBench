#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct shader_reg {int dummy; } ;
struct asm_parser {TYPE_1__* shader; } ;
struct TYPE_4__ {struct shader_reg predicate; int /*<<< orphan*/  has_predicate; } ;
struct TYPE_3__ {int num_instrs; TYPE_2__** instr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void asmparser_predicate_supported(struct asm_parser *This,
                                          const struct shader_reg *predicate) {
    /* this sets the predicate of the last instruction added to the shader */
    if(!This->shader) return;
    if(This->shader->num_instrs == 0) ERR("Predicate without an instruction\n");
    This->shader->instr[This->shader->num_instrs - 1]->has_predicate = TRUE;
    This->shader->instr[This->shader->num_instrs - 1]->predicate = *predicate;
}