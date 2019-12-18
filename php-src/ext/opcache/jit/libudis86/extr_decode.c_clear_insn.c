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
struct ud {TYPE_1__* operand; scalar_t__ _rex; scalar_t__ vex_op; scalar_t__ br_far; scalar_t__ have_modrm; int /*<<< orphan*/ * itab_entry; int /*<<< orphan*/  mnemonic; scalar_t__ pfx_str; scalar_t__ pfx_rex; scalar_t__ pfx_repe; scalar_t__ pfx_rep; scalar_t__ pfx_repne; scalar_t__ pfx_lock; scalar_t__ pfx_adr; scalar_t__ pfx_opr; scalar_t__ pfx_seg; scalar_t__ error; } ;
struct TYPE_2__ {void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_Inone ; 
 void* UD_NONE ; 

__attribute__((used)) static void
clear_insn(register struct ud* u)
{
  u->error     = 0;
  u->pfx_seg   = 0;
  u->pfx_opr   = 0;
  u->pfx_adr   = 0;
  u->pfx_lock  = 0;
  u->pfx_repne = 0;
  u->pfx_rep   = 0;
  u->pfx_repe  = 0;
  u->pfx_rex   = 0;
  u->pfx_str   = 0;
  u->mnemonic  = UD_Inone;
  u->itab_entry = NULL;
  u->have_modrm = 0;
  u->br_far    = 0;
  u->vex_op    = 0;
  u->_rex      = 0;
  u->operand[0].type = UD_NONE;
  u->operand[1].type = UD_NONE;
  u->operand[2].type = UD_NONE;
  u->operand[3].type = UD_NONE;
}