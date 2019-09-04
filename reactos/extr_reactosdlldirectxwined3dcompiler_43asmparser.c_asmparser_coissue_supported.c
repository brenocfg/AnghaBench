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
struct asm_parser {TYPE_2__* shader; int /*<<< orphan*/  status; int /*<<< orphan*/  line_no; } ;
struct TYPE_4__ {int num_instrs; TYPE_1__** instr; } ;
struct TYPE_3__ {int /*<<< orphan*/  coissue; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_ERR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  asmparser_message (struct asm_parser*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_parse_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asmparser_coissue_supported(struct asm_parser *This) {
    /* this sets the coissue flag of the last instruction added to the shader */
    if(!This->shader) return;
    if(This->shader->num_instrs == 0){
        asmparser_message(This, "Line %u: Coissue flag on the first shader instruction\n", This->line_no);
        set_parse_status(&This->status, PARSE_ERR);
    }
    This->shader->instr[This->shader->num_instrs-1]->coissue = TRUE;
}