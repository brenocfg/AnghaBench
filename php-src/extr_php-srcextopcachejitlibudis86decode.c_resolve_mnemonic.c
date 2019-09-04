#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ud {scalar_t__ mnemonic; int dis_mode; scalar_t__ pfx_repe; TYPE_2__* operand; TYPE_1__* le; } ;
struct TYPE_6__ {scalar_t__ mnemonic; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ base; } ;
struct TYPE_4__ {size_t* table; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDERR (struct ud*,char*) ; 
 scalar_t__ UD_I3dnow ; 
 scalar_t__ UD_Inop ; 
 scalar_t__ UD_Ipause ; 
 scalar_t__ UD_Iswapgs ; 
 scalar_t__ UD_Ixchg ; 
 void* UD_NONE ; 
 scalar_t__ UD_OP_REG ; 
 scalar_t__ UD_R_AX ; 
 scalar_t__ UD_R_EAX ; 
 size_t inp_curr (struct ud*) ; 
 TYPE_3__* ud_itab ; 

__attribute__((used)) static int resolve_mnemonic( struct ud* u )
{
  /* resolve 3dnow weirdness. */
  if ( u->mnemonic == UD_I3dnow ) {
    u->mnemonic = ud_itab[ u->le->table[ inp_curr( u )  ] ].mnemonic;
  }
  /* SWAPGS is only valid in 64bits mode */
  if ( u->mnemonic == UD_Iswapgs && u->dis_mode != 64 ) {
    UDERR(u, "swapgs invalid in 64bits mode\n");
    return -1;
  }

  if (u->mnemonic == UD_Ixchg) {
    if ((u->operand[0].type == UD_OP_REG && u->operand[0].base == UD_R_AX  &&
         u->operand[1].type == UD_OP_REG && u->operand[1].base == UD_R_AX) ||
        (u->operand[0].type == UD_OP_REG && u->operand[0].base == UD_R_EAX &&
         u->operand[1].type == UD_OP_REG && u->operand[1].base == UD_R_EAX)) {
      u->operand[0].type = UD_NONE;
      u->operand[1].type = UD_NONE;
      u->mnemonic = UD_Inop;
    }
  }

  if (u->mnemonic == UD_Inop && u->pfx_repe) {
    u->pfx_repe = 0;
    u->mnemonic = UD_Ipause;
  }
  return 0;
}