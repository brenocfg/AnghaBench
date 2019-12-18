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
struct constant {scalar_t__ const regnum; TYPE_1__* value; } ;
struct bytecode_buffer {int dummy; } ;
struct TYPE_2__ {scalar_t__ const d; } ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ D3DSIO_DEFB ; 
 int D3DSI_INSTLENGTH_SHIFT ; 
 scalar_t__ const D3DSP_REGNUM_MASK ; 
 unsigned int D3DSP_WRITEMASK_ALL ; 
 unsigned int d3dsp_register (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,scalar_t__ const) ; 

__attribute__((used)) static void write_const(struct constant **consts, int num, DWORD opcode, DWORD reg_type, struct bytecode_buffer *buffer, BOOL len) {
    int i;
    DWORD instr_def = opcode;
    const DWORD reg = (1u << 31) | d3dsp_register( reg_type, 0 ) | D3DSP_WRITEMASK_ALL;

    if(len) {
        if(opcode == D3DSIO_DEFB)
            instr_def |= 2 << D3DSI_INSTLENGTH_SHIFT;
        else
            instr_def |= 5 << D3DSI_INSTLENGTH_SHIFT;
    }

    for(i = 0; i < num; i++) {
        /* Write the DEF instruction */
        put_dword(buffer, instr_def);

        put_dword(buffer, reg | (consts[i]->regnum & D3DSP_REGNUM_MASK));
        put_dword(buffer, consts[i]->value[0].d);
        if(opcode != D3DSIO_DEFB) {
            put_dword(buffer, consts[i]->value[1].d);
            put_dword(buffer, consts[i]->value[2].d);
            put_dword(buffer, consts[i]->value[3].d);
        }
    }
}