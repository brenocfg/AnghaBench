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
struct instruction {scalar_t__ has_predicate; scalar_t__ comptype; int /*<<< orphan*/  num_srcs; scalar_t__ has_dst; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int D3DSHADER_INSTRUCTION_PREDICATED ; 
 int D3DSI_INSTLENGTH_SHIFT ; 
 int d3d9_comparetype (scalar_t__) ; 
 int instrlen (struct instruction const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 

__attribute__((used)) static void sm_2_opcode(struct bc_writer *This,
                        const struct instruction *instr,
                        DWORD token, struct bytecode_buffer *buffer) {
    /* From sm 2 onwards instruction length is encoded in the opcode field */
    int dsts = instr->has_dst ? 1 : 0;
    token |= instrlen(instr, instr->num_srcs, dsts) << D3DSI_INSTLENGTH_SHIFT;
    if(instr->comptype)
        token |= (d3d9_comparetype(instr->comptype) << 16) & (0xf << 16);
    if(instr->has_predicate)
        token |= D3DSHADER_INSTRUCTION_PREDICATED;
    put_dword(buffer,token);
}