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
typedef  unsigned long long const uint64_t ;
struct TYPE_2__ {unsigned long long const sbyte; unsigned long long const sword; unsigned long long const sdword; } ;
struct ud_operand {int size; TYPE_1__ lval; } ;
struct ud {int adr_mode; int opr_mode; unsigned long long const pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  UD_ASSERT (int) ; 

uint64_t
ud_syn_rel_target(struct ud *u, struct ud_operand *opr)
{
#if 1
  const uint64_t trunc_mask = 0xffffffffffffffffull >> (64 - u->adr_mode);
#else
  const uint64_t trunc_mask = 0xffffffffffffffffull >> (64 - u->opr_mode);
#endif
  switch (opr->size) {
  case 8 : return (u->pc + opr->lval.sbyte)  & trunc_mask;
  case 16: return (u->pc + opr->lval.sword)  & trunc_mask;
  case 32: return (u->pc + opr->lval.sdword) & trunc_mask;
  default: UD_ASSERT(!"invalid relative offset size.");
    return 0ull;
  }
}