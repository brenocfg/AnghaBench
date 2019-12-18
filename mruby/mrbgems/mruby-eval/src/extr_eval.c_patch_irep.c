#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_9__ {int flags; int ilen; TYPE_5__* lv; int /*<<< orphan*/  nlocals; int /*<<< orphan*/ * syms; struct TYPE_9__** reps; scalar_t__ iseq; } ;
typedef  TYPE_1__ mrb_irep ;
typedef  int mrb_code ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MRB_ISEQ_NO_FREE ; 
#define  OP_BLOCK 137 
#define  OP_EPUSH 136 
#define  OP_EXT1 135 
#define  OP_EXT2 134 
#define  OP_EXT3 133 
#define  OP_GETUPVAR 132 
#define  OP_LAMBDA 131 
#define  OP_MOVE 130 
#define  OP_SEND 129 
#define  OP_SETUPVAR 128 
 void* PEEK_B (int*) ; 
 size_t PEEK_S (int*) ; 
 int irep_argc (TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 scalar_t__* mrb_insn_size ; 
 int /*<<< orphan*/ * mrb_insn_size1 ; 
 int /*<<< orphan*/ * mrb_insn_size2 ; 
 int /*<<< orphan*/ * mrb_insn_size3 ; 
 int /*<<< orphan*/  potential_upvar_p (TYPE_5__*,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* search_irep (TYPE_1__*,int,int,TYPE_1__*) ; 
 size_t search_variable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
patch_irep(mrb_state *mrb, mrb_irep *irep, int bnest, mrb_irep *top)
{
  int i;
  uint32_t a;
  uint16_t b;
  uint8_t c;
  mrb_code insn;
  int argc = irep_argc(irep);
  mrb_code *iseq = (mrb_code *)irep->iseq;

  mrb_assert((irep->flags & MRB_ISEQ_NO_FREE) == 0);

  for (i = 0; i < irep->ilen; ) {
    insn = iseq[i];
    switch(insn){
    case OP_EPUSH:
      b = PEEK_S(iseq+i+1);
      patch_irep(mrb, irep->reps[b], bnest + 1, top);
      break;

    case OP_LAMBDA:
    case OP_BLOCK:
      a = PEEK_B(iseq+i+1);
      b = PEEK_B(iseq+i+2);
      patch_irep(mrb, irep->reps[b], bnest + 1, top);
      break;

    case OP_SEND:
      b = PEEK_B(iseq+i+2);
      c = PEEK_B(iseq+i+3);
      if (c != 0) {
        break;
      }
      else {
        uint16_t arg = search_variable(mrb, irep->syms[b], bnest);
        if (arg != 0) {
          /* must replace */
          iseq[i] = OP_GETUPVAR;
          iseq[i+2] = arg >> 8;
          iseq[i+3] = arg & 0xff;
        }
      }
      break;

    case OP_MOVE:
      a = PEEK_B(iseq+i+1);
      b = PEEK_B(iseq+i+2);
      /* src part */
      if (potential_upvar_p(irep->lv, b, argc, irep->nlocals)) {
        uint16_t arg = search_variable(mrb, irep->lv[b - 1].name, bnest);
        if (arg != 0) {
          /* must replace */
          iseq[i] = insn = OP_GETUPVAR;
          iseq[i+2] = arg >> 8;
          iseq[i+3] = arg & 0xff;
        }
      }
      /* dst part */
      if (potential_upvar_p(irep->lv, a, argc, irep->nlocals)) {
        uint16_t arg = search_variable(mrb, irep->lv[a - 1].name, bnest);
        if (arg != 0) {
          /* must replace */
          iseq[i] = insn = OP_SETUPVAR;
          iseq[i+1] = (mrb_code)b;
          iseq[i+2] = arg >> 8;
          iseq[i+3] = arg & 0xff;
        }
      }
      break;

    case OP_GETUPVAR:
      a = PEEK_B(iseq+i+1);
      b = PEEK_B(iseq+i+2);
      c = PEEK_B(iseq+i+3);
      {
        int lev = c+1;
        mrb_irep *tmp = search_irep(top, bnest, lev, irep);
        if (potential_upvar_p(tmp->lv, b, irep_argc(tmp), tmp->nlocals)) {
          uint16_t arg = search_variable(mrb, tmp->lv[b-1].name, bnest);
          if (arg != 0) {
            /* must replace */
            iseq[i] = OP_GETUPVAR;
            iseq[i+2] = arg >> 8;
            iseq[i+3] = arg & 0xff;
          }
        }
      }
      break;

    case OP_SETUPVAR:
      a = PEEK_B(iseq+i+1);
      b = PEEK_B(iseq+i+2);
      c = PEEK_B(iseq+i+3);
      {
        int lev = c+1;
        mrb_irep *tmp = search_irep(top, bnest, lev, irep);
        if (potential_upvar_p(tmp->lv, b, irep_argc(tmp), tmp->nlocals)) {
          uint16_t arg = search_variable(mrb, tmp->lv[b-1].name, bnest);
          if (arg != 0) {
            /* must replace */
            iseq[i] = OP_SETUPVAR;
            iseq[i+1] = a;
            iseq[i+2] = arg >> 8;
            iseq[i+3] = arg & 0xff;
          }
        }
      }
      break;

    case OP_EXT1:
      insn = PEEK_B(iseq+i+1);
      i += mrb_insn_size1[insn]+1;
      continue;
    case OP_EXT2:
      insn = PEEK_B(iseq+i+1);
      i += mrb_insn_size2[insn]+1;
      continue;
    case OP_EXT3:
      insn = PEEK_B(iseq+i+1);
      i += mrb_insn_size3[insn]+1;
      continue;
    }
    i+=mrb_insn_size[insn];
  }
}