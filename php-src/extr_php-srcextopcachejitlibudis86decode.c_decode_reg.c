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
struct ud_operand {int base; int size; int /*<<< orphan*/  type; } ;
struct ud {int dummy; } ;

/* Variables and functions */
#define  REGCLASS_CR 133 
#define  REGCLASS_DB 132 
#define  REGCLASS_GPR 131 
#define  REGCLASS_MMX 130 
#define  REGCLASS_SEG 129 
#define  REGCLASS_XMM 128 
 int SZ_QQ ; 
 int /*<<< orphan*/  UDERR (struct ud*,char*) ; 
 int /*<<< orphan*/  UD_ASSERT (int) ; 
 int /*<<< orphan*/  UD_OP_REG ; 
 int /*<<< orphan*/  UD_R_CR0 ; 
 int /*<<< orphan*/  UD_R_DR0 ; 
 int /*<<< orphan*/  UD_R_ES ; 
 int /*<<< orphan*/  UD_R_MM0 ; 
 int /*<<< orphan*/  UD_R_XMM0 ; 
 int /*<<< orphan*/  UD_R_YMM0 ; 
 int decode_gpr (struct ud*,int,int) ; 
 int resolve_operand_size (struct ud*,int) ; 

__attribute__((used)) static void
decode_reg(struct ud *u, 
           struct ud_operand *opr,
           int type,
           int num,
           int size)
{
  int reg;
  size = resolve_operand_size(u, size);
  switch (type) {
    case REGCLASS_GPR : reg = decode_gpr(u, size, num); break;
    case REGCLASS_MMX : reg = UD_R_MM0  + (num & 7); break;
    case REGCLASS_XMM :
      reg = num + (size == SZ_QQ ? UD_R_YMM0 : UD_R_XMM0);
      break;
    case REGCLASS_CR : reg = UD_R_CR0  + num; break;
    case REGCLASS_DB : reg = UD_R_DR0  + num; break;
    case REGCLASS_SEG : {
      /*
       * Only 6 segment registers, anything else is an error.
       */
      if ((num & 7) > 5) {
        UDERR(u, "invalid segment register value\n");
        return;
      } else {
        reg = UD_R_ES + (num & 7);
      }
      break;
    }
    default:
      UD_ASSERT(!"invalid register type");
      return;
  }
  opr->type = UD_OP_REG;
  opr->base = reg;
  opr->size = size;
}