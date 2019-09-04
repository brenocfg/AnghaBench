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
typedef  size_t uint8_t ;
typedef  int uint16_t ;
struct ud {int dis_mode; TYPE_1__* le; int /*<<< orphan*/  vendor; int /*<<< orphan*/  pfx_adr; int /*<<< orphan*/  pfx_opr; int /*<<< orphan*/  pfx_rex; } ;
struct TYPE_2__ {int type; int* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODRM_MOD (int /*<<< orphan*/ ) ; 
 size_t MODRM_REG (int /*<<< orphan*/ ) ; 
 size_t MODRM_RM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REX_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UD_ASSERT (int) ; 
 int UD_TAB__OPC_3DNOW ; 
#define  UD_TAB__OPC_ASIZE 140 
#define  UD_TAB__OPC_MOD 139 
#define  UD_TAB__OPC_MODE 138 
#define  UD_TAB__OPC_OSIZE 137 
#define  UD_TAB__OPC_REG 136 
#define  UD_TAB__OPC_RM 135 
#define  UD_TAB__OPC_SSE 134 
#define  UD_TAB__OPC_TABLE 133 
#define  UD_TAB__OPC_VENDOR 132 
#define  UD_TAB__OPC_VEX 131 
#define  UD_TAB__OPC_VEX_L 130 
#define  UD_TAB__OPC_VEX_W 129 
#define  UD_TAB__OPC_X87 128 
 int /*<<< orphan*/  UD_VENDOR_AMD ; 
 int /*<<< orphan*/  UD_VENDOR_ANY ; 
 int decode_3dnow (struct ud*) ; 
 int decode_insn (struct ud*,int) ; 
 int decode_opcode (struct ud*) ; 
 int decode_ssepfx (struct ud*) ; 
 int decode_vex (struct ud*) ; 
 int eff_adr_mode (int,int /*<<< orphan*/ ) ; 
 int eff_opr_mode (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inp_next (struct ud*) ; 
 int /*<<< orphan*/  modrm (struct ud*) ; 
 TYPE_1__* ud_lookup_table_list ; 
 size_t vex_l (struct ud*) ; 
 size_t vex_w (struct ud*) ; 

__attribute__((used)) static int
decode_ext(struct ud *u, uint16_t ptr)
{
  uint8_t idx = 0;
  if ((ptr & 0x8000) == 0) {
    return decode_insn(u, ptr); 
  }
  u->le = &ud_lookup_table_list[(~0x8000 & ptr)];
  if (u->le->type == UD_TAB__OPC_3DNOW) {
    return decode_3dnow(u);
  }

  switch (u->le->type) {
    case UD_TAB__OPC_MOD:
      /* !11 = 0, 11 = 1 */
      idx = (MODRM_MOD(modrm(u)) + 1) / 4;
      break;
      /* disassembly mode/operand size/address size based tables.
       * 16 = 0,, 32 = 1, 64 = 2
       */
    case UD_TAB__OPC_MODE:
      idx = u->dis_mode != 64 ? 0 : 1;
      break;
    case UD_TAB__OPC_OSIZE:
      idx = eff_opr_mode(u->dis_mode, REX_W(u->pfx_rex), u->pfx_opr) / 32;
      break;
    case UD_TAB__OPC_ASIZE:
      idx = eff_adr_mode(u->dis_mode, u->pfx_adr) / 32;
      break;
    case UD_TAB__OPC_X87:
      idx = modrm(u) - 0xC0;
      break;
    case UD_TAB__OPC_VENDOR:
      if (u->vendor == UD_VENDOR_ANY) {
        /* choose a valid entry */
        idx = (u->le->table[idx] != 0) ? 0 : 1;
      } else if (u->vendor == UD_VENDOR_AMD) {
        idx = 0;
      } else {
        idx = 1;
      }
      break;
    case UD_TAB__OPC_RM:
      idx = MODRM_RM(modrm(u));
      break;
    case UD_TAB__OPC_REG:
      idx = MODRM_REG(modrm(u));
      break;
    case UD_TAB__OPC_SSE:
      return decode_ssepfx(u);
    case UD_TAB__OPC_VEX:
      return decode_vex(u);
    case UD_TAB__OPC_VEX_W:
      idx = vex_w(u);
      break;
    case UD_TAB__OPC_VEX_L:
      idx = vex_l(u);
      break;
    case UD_TAB__OPC_TABLE:
      inp_next(u);
      return decode_opcode(u);
    default:
      UD_ASSERT(!"not reached");
      break;
  }

  return decode_ext(u, u->le->table[idx]);
}