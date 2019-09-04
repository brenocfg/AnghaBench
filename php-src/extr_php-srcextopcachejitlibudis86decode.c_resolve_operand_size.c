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
typedef  int ud_operand_size_t ;
struct ud {unsigned int opr_mode; int dis_mode; TYPE_1__* itab_entry; int /*<<< orphan*/  vex_op; } ;
struct TYPE_2__ {int /*<<< orphan*/  prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_VEXL (int /*<<< orphan*/ ) ; 
 unsigned int SZ_DQ ; 
 unsigned int SZ_QQ ; 
#define  SZ_RDQ 132 
#define  SZ_V 131 
#define  SZ_X 130 
#define  SZ_Y 129 
#define  SZ_Z 128 
 int /*<<< orphan*/  UD_ASSERT (int) ; 
 int /*<<< orphan*/  vex_l (struct ud const*) ; 

__attribute__((used)) static unsigned int
resolve_operand_size(const struct ud* u, ud_operand_size_t osize)
{
  switch (osize) {
  case SZ_V:
    return u->opr_mode;
  case SZ_Z:  
    return u->opr_mode == 16 ? 16 : 32;
  case SZ_Y:
    return u->opr_mode == 16 ? 32 : u->opr_mode;
  case SZ_RDQ:
    return u->dis_mode == 64 ? 64 : 32;
  case SZ_X:
    UD_ASSERT(u->vex_op != 0);
    return (P_VEXL(u->itab_entry->prefix) && vex_l(u)) ?  SZ_QQ : SZ_DQ;
  default:
    return osize;
  }
}