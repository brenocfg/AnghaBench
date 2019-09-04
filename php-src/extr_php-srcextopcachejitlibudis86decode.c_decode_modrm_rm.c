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
struct ud_operand {scalar_t__ base; scalar_t__ index; unsigned int scale; scalar_t__ offset; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct ud {int adr_mode; int /*<<< orphan*/  pfx_rex; int /*<<< orphan*/  _rex; } ;

/* Variables and functions */
 unsigned char MODRM_MOD (int /*<<< orphan*/ ) ; 
 int MODRM_RM (int /*<<< orphan*/ ) ; 
 int REX_B (int /*<<< orphan*/ ) ; 
 int REX_X (int /*<<< orphan*/ ) ; 
 int SIB_B (int /*<<< orphan*/ ) ; 
 int SIB_I (int /*<<< orphan*/ ) ; 
 int SIB_S (int /*<<< orphan*/ ) ; 
 unsigned int const UD_NONE ; 
 int /*<<< orphan*/  UD_OP_MEM ; 
 unsigned int const UD_R_BP ; 
 unsigned int const UD_R_BX ; 
 unsigned int const UD_R_DI ; 
 void* UD_R_EAX ; 
 scalar_t__ UD_R_EBP ; 
 scalar_t__ UD_R_ESP ; 
 scalar_t__ UD_R_R13 ; 
 void* UD_R_RAX ; 
 scalar_t__ UD_R_RBP ; 
 scalar_t__ UD_R_RIP ; 
 scalar_t__ UD_R_RSP ; 
 unsigned int const UD_R_SI ; 
 int /*<<< orphan*/  decode_mem_disp (struct ud*,size_t,struct ud_operand*) ; 
 int /*<<< orphan*/  decode_reg (struct ud*,struct ud_operand*,unsigned char,unsigned char,unsigned int) ; 
 int /*<<< orphan*/  inp_curr (struct ud*) ; 
 int /*<<< orphan*/  inp_next (struct ud*) ; 
 int /*<<< orphan*/  modrm (struct ud*) ; 
 int /*<<< orphan*/  resolve_operand_size (struct ud*,unsigned int) ; 

__attribute__((used)) static void 
decode_modrm_rm(struct ud         *u, 
                struct ud_operand *op,
                unsigned char      type,    /* register type */
                unsigned int       size)    /* operand size */

{
  size_t offset = 0;
  unsigned char mod, rm;

  /* get mod, r/m and reg fields */
  mod = MODRM_MOD(modrm(u));
  rm  = (REX_B(u->_rex) << 3) | MODRM_RM(modrm(u));

  /* 
   * If mod is 11b, then the modrm.rm specifies a register.
   *
   */
  if (mod == 3) {
    decode_reg(u, op, type, rm, size);
    return;
  }

  /* 
   * !11b => Memory Address
   */  
  op->type = UD_OP_MEM;
  op->size = resolve_operand_size(u, size);

  if (u->adr_mode == 64) {
    op->base = UD_R_RAX + rm;
    if (mod == 1) {
      offset = 8;
    } else if (mod == 2) {
      offset = 32;
    } else if (mod == 0 && (rm & 7) == 5) {           
      op->base = UD_R_RIP;
      offset = 32;
    } else {
      offset = 0;
    }
    /* 
     * Scale-Index-Base (SIB) 
     */
    if ((rm & 7) == 4) {
      inp_next(u);
      
      op->base  = UD_R_RAX + (SIB_B(inp_curr(u)) | (REX_B(u->_rex) << 3));
      op->index = UD_R_RAX + (SIB_I(inp_curr(u)) | (REX_X(u->_rex) << 3));
      /* special conditions for base reference */
      if (op->index == UD_R_RSP) {
        op->index = UD_NONE;
        op->scale = UD_NONE;
      } else {
        op->scale = (1 << SIB_S(inp_curr(u))) & ~1;
      }

      if (op->base == UD_R_RBP || op->base == UD_R_R13) {
        if (mod == 0) {
          op->base = UD_NONE;
        } 
        if (mod == 1) {
          offset = 8;
        } else {
          offset = 32;
        }
      }
    } else {
        op->scale = UD_NONE;
        op->index = UD_NONE;
    }
  } else if (u->adr_mode == 32) {
    op->base = UD_R_EAX + rm;
    if (mod == 1) {
      offset = 8;
    } else if (mod == 2) {
      offset = 32;
    } else if (mod == 0 && rm == 5) {
      op->base = UD_NONE;
      offset = 32;
    } else {
      offset = 0;
    }

    /* Scale-Index-Base (SIB) */
    if ((rm & 7) == 4) {
      inp_next(u);

      op->scale = (1 << SIB_S(inp_curr(u))) & ~1;
      op->index = UD_R_EAX + (SIB_I(inp_curr(u)) | (REX_X(u->pfx_rex) << 3));
      op->base  = UD_R_EAX + (SIB_B(inp_curr(u)) | (REX_B(u->pfx_rex) << 3));

      if (op->index == UD_R_ESP) {
        op->index = UD_NONE;
        op->scale = UD_NONE;
      }

      /* special condition for base reference */
      if (op->base == UD_R_EBP) {
        if (mod == 0) {
          op->base = UD_NONE;
        } 
        if (mod == 1) {
          offset = 8;
        } else {
          offset = 32;
        }
      }
    } else {
      op->scale = UD_NONE;
      op->index = UD_NONE;
    }
  } else {
    const unsigned int bases[]   = { UD_R_BX, UD_R_BX, UD_R_BP, UD_R_BP,
                                     UD_R_SI, UD_R_DI, UD_R_BP, UD_R_BX };
    const unsigned int indices[] = { UD_R_SI, UD_R_DI, UD_R_SI, UD_R_DI,
                                     UD_NONE, UD_NONE, UD_NONE, UD_NONE };
    op->base  = bases[rm & 7];
    op->index = indices[rm & 7];
    op->scale = UD_NONE;
    if (mod == 0 && rm == 6) {
      offset = 16;
      op->base = UD_NONE;
    } else if (mod == 1) {
      offset = 8;
    } else if (mod == 2) { 
      offset = 16;
    }
  }

  if (offset) {
    decode_mem_disp(u, offset, op);
  } else {
    op->offset = 0;
  }
}