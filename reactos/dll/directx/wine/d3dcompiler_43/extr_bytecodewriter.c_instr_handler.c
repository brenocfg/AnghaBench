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
struct instruction {int /*<<< orphan*/  dstmod; int /*<<< orphan*/  shift; int /*<<< orphan*/  dst; scalar_t__ has_dst; int /*<<< orphan*/  opcode; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dstreg ) (struct bc_writer*,int /*<<< orphan*/ *,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* opcode ) (struct bc_writer*,struct instruction const*,int /*<<< orphan*/ ,struct bytecode_buffer*) ;} ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_opcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct bc_writer*,struct instruction const*,int /*<<< orphan*/ ,struct bytecode_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct bc_writer*,int /*<<< orphan*/ *,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_srcregs (struct bc_writer*,struct instruction const*,struct bytecode_buffer*) ; 

__attribute__((used)) static void instr_handler(struct bc_writer *This,
                          const struct instruction *instr,
                          struct bytecode_buffer *buffer) {
    DWORD token = d3d9_opcode(instr->opcode);

    This->funcs->opcode(This, instr, token, buffer);
    if(instr->has_dst) This->funcs->dstreg(This, &instr->dst, buffer, instr->shift, instr->dstmod);
    write_srcregs(This, instr, buffer);
}