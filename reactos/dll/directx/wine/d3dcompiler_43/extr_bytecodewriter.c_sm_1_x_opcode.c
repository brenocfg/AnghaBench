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
struct instruction {scalar_t__ coissue; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DSI_COISSUE ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sm_1_x_opcode(struct bc_writer *This,
                          const struct instruction *instr,
                          DWORD token, struct bytecode_buffer *buffer) {
    /* In sm_1_x instruction length isn't encoded */
    if(instr->coissue){
        token |= D3DSI_COISSUE;
    }
    put_dword(buffer, token);
}