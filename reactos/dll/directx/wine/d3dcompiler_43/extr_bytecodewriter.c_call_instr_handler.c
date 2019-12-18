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
struct instruction {scalar_t__ opcode; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {TYPE_1__* funcs; } ;
struct TYPE_4__ {scalar_t__ opcode; int /*<<< orphan*/  (* func ) (struct bc_writer*,struct instruction const*,struct bytecode_buffer*) ;} ;
struct TYPE_3__ {TYPE_2__* instructions; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ BWRITERSIO_END ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,scalar_t__) ; 
 int /*<<< orphan*/  debug_print_opcode (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct bc_writer*,struct instruction const*,struct bytecode_buffer*) ; 

__attribute__((used)) static HRESULT call_instr_handler(struct bc_writer *writer,
                                  const struct instruction *instr,
                                  struct bytecode_buffer *buffer) {
    DWORD i=0;

    while(writer->funcs->instructions[i].opcode != BWRITERSIO_END) {
        if(instr->opcode == writer->funcs->instructions[i].opcode) {
            if(!writer->funcs->instructions[i].func) {
                WARN("Opcode %u not supported by this profile\n", instr->opcode);
                return E_INVALIDARG;
            }
            writer->funcs->instructions[i].func(writer, instr, buffer);
            return S_OK;
        }
        i++;
    }

    FIXME("Unhandled instruction %u - %s\n", instr->opcode,
          debug_print_opcode(instr->opcode));
    return E_INVALIDARG;
}