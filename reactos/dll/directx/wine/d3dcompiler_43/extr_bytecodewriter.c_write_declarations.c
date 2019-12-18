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
struct TYPE_3__ {int /*<<< orphan*/  writemask; } ;
struct shader_reg {int type; TYPE_1__ u; int /*<<< orphan*/  regnum; } ;
struct declaration {int usage; int usage_idx; int /*<<< orphan*/  mod; int /*<<< orphan*/  writemask; int /*<<< orphan*/  regnum; scalar_t__ builtin; } ;
struct bytecode_buffer {int dummy; } ;
struct bc_writer {TYPE_2__* funcs; } ;
typedef  int /*<<< orphan*/  reg ;
struct TYPE_4__ {int /*<<< orphan*/  (* dstreg ) (struct bc_writer*,struct shader_reg*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int D3DSIO_DCL ; 
 int D3DSI_INSTLENGTH_SHIFT ; 
 int D3DSP_DCL_USAGEINDEX_MASK ; 
 int D3DSP_DCL_USAGEINDEX_SHIFT ; 
 int D3DSP_DCL_USAGE_MASK ; 
 int D3DSP_DCL_USAGE_SHIFT ; 
 int /*<<< orphan*/  ZeroMemory (struct shader_reg*,int) ; 
 int /*<<< orphan*/  put_dword (struct bytecode_buffer*,int) ; 
 int /*<<< orphan*/  stub1 (struct bc_writer*,struct shader_reg*,struct bytecode_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_declarations(struct bc_writer *This,
                               struct bytecode_buffer *buffer, BOOL len,
                               const struct declaration *decls, unsigned int num, DWORD type) {
    DWORD i;
    DWORD instr_dcl = D3DSIO_DCL;
    DWORD token;
    struct shader_reg reg;

    ZeroMemory(&reg, sizeof(reg));

    if(len) {
        instr_dcl |= 2 << D3DSI_INSTLENGTH_SHIFT;
    }

    for(i = 0; i < num; i++) {
        if(decls[i].builtin) continue;

        /* Write the DCL instruction */
        put_dword(buffer, instr_dcl);

        /* Write the usage and index */
        token = (1u << 31); /* Bit 31 of non-instruction opcodes is 1 */
        token |= (decls[i].usage << D3DSP_DCL_USAGE_SHIFT) & D3DSP_DCL_USAGE_MASK;
        token |= (decls[i].usage_idx << D3DSP_DCL_USAGEINDEX_SHIFT) & D3DSP_DCL_USAGEINDEX_MASK;
        put_dword(buffer, token);

        /* Write the dest register */
        reg.type = type;
        reg.regnum = decls[i].regnum;
        reg.u.writemask = decls[i].writemask;
        This->funcs->dstreg(This, &reg, buffer, 0, decls[i].mod);
    }
}