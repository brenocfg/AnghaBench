#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ud {int dis_mode; size_t pfx_seg; int mnemonic; TYPE_2__* operand; scalar_t__ pfx_repne; scalar_t__ pfx_repe; scalar_t__ pfx_rep; scalar_t__ pfx_lock; scalar_t__ pfx_adr; TYPE_1__* itab_entry; scalar_t__ pfx_opr; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ size; scalar_t__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_ASO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_OSO (int /*<<< orphan*/ ) ; 
#define  UD_Ircl 134 
#define  UD_Ircr 133 
#define  UD_Irol 132 
#define  UD_Iror 131 
#define  UD_Isar 130 
#define  UD_Ishl 129 
#define  UD_Ishr 128 
 scalar_t__ UD_NONE ; 
 scalar_t__ UD_OP_CONST ; 
 scalar_t__ UD_OP_IMM ; 
 scalar_t__ UD_OP_MEM ; 
 scalar_t__ UD_OP_REG ; 
 size_t UD_R_AL ; 
 scalar_t__ UD_R_CL ; 
 int /*<<< orphan*/  gen_operand (struct ud*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ud_asmprintf (struct ud*,char*,...) ; 
 int /*<<< orphan*/  ud_lookup_mnemonic (int) ; 
 int /*<<< orphan*/  ud_opr_is_sreg (TYPE_2__*) ; 
 int /*<<< orphan*/ * ud_reg_tab ; 

extern void
ud_translate_intel(struct ud* u)
{
  /* check if P_OSO prefix is used */
  if (!P_OSO(u->itab_entry->prefix) && u->pfx_opr) {
    switch (u->dis_mode) {
    case 16: ud_asmprintf(u, "o32 "); break;
    case 32:
    case 64: ud_asmprintf(u, "o16 "); break;
    }
  }

  /* check if P_ASO prefix was used */
  if (!P_ASO(u->itab_entry->prefix) && u->pfx_adr) {
    switch (u->dis_mode) {
    case 16: ud_asmprintf(u, "a32 "); break;
    case 32: ud_asmprintf(u, "a16 "); break;
    case 64: ud_asmprintf(u, "a32 "); break;
    }
  }

  if (u->pfx_seg &&
      u->operand[0].type != UD_OP_MEM &&
      u->operand[1].type != UD_OP_MEM ) {
    ud_asmprintf(u, "%s ", ud_reg_tab[u->pfx_seg - UD_R_AL]);
  }

  if (u->pfx_lock) {
    ud_asmprintf(u, "lock ");
  }
  if (u->pfx_rep) {
    ud_asmprintf(u, "rep ");
  } else if (u->pfx_repe) {
    ud_asmprintf(u, "repe ");
  } else if (u->pfx_repne) {
    ud_asmprintf(u, "repne ");
  }

  /* print the instruction mnemonic */
  ud_asmprintf(u, "%s", ud_lookup_mnemonic(u->mnemonic));

  if (u->operand[0].type != UD_NONE) {
    int cast = 0;
    ud_asmprintf(u, " ");
    if (u->operand[0].type == UD_OP_MEM) {
      if (u->operand[1].type == UD_OP_IMM   ||
          u->operand[1].type == UD_OP_CONST ||
          u->operand[1].type == UD_NONE     ||
          (u->operand[0].size != u->operand[1].size)) {
          cast = 1;
      } else if (u->operand[1].type == UD_OP_REG &&
                 u->operand[1].base == UD_R_CL) {
          switch (u->mnemonic) {
          case UD_Ircl:
          case UD_Irol:
          case UD_Iror:
          case UD_Ircr:
          case UD_Ishl:
          case UD_Ishr:
          case UD_Isar:
              cast = 1;
              break;
          default: break;
          }
      }
    }
    gen_operand(u, &u->operand[0], cast);
  }

  if (u->operand[1].type != UD_NONE) {
    int cast = 0;
    ud_asmprintf(u, ", ");
    if (u->operand[1].type == UD_OP_MEM &&
        u->operand[0].size != u->operand[1].size && 
        !ud_opr_is_sreg(&u->operand[0])) {
      cast = 1;
    }
    gen_operand(u, &u->operand[1], cast);
  }

  if (u->operand[2].type != UD_NONE) {
    int cast = 0;
    ud_asmprintf(u, ", ");
    if (u->operand[2].type == UD_OP_MEM &&
        u->operand[2].size != u->operand[1].size) {
      cast = 1;
    }
    gen_operand(u, &u->operand[2], cast);
  }

  if (u->operand[3].type != UD_NONE) {
    ud_asmprintf(u, ", ");
    gen_operand(u, &u->operand[3], 0);
  }
}