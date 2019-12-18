#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct mrb_insn_data {scalar_t__ insn; scalar_t__ a; scalar_t__ b; } ;
typedef  int /*<<< orphan*/  mrb_code ;
struct TYPE_7__ {scalar_t__ pc; scalar_t__ lastpc; } ;
typedef  TYPE_1__ codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  OP_EXT1 ; 
 scalar_t__ OP_MOVE ; 
 int /*<<< orphan*/  gen_B (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_S (TYPE_1__*,int) ; 
 struct mrb_insn_data mrb_last_insn (TYPE_1__*) ; 
 int /*<<< orphan*/  no_peephole (TYPE_1__*) ; 

__attribute__((used)) static uint16_t
genjmp2(codegen_scope *s, mrb_code i, uint16_t a, int pc, int val)
{
  uint16_t pos;

  if (!no_peephole(s) && !val) {
    struct mrb_insn_data data = mrb_last_insn(s);

    if (data.insn == OP_MOVE && data.a == a) {
      s->pc = s->lastpc;
      a = data.b;
    }
  }

  s->lastpc = s->pc;
  if (a > 0xff) {
    gen_B(s, OP_EXT1);
    gen_B(s, i);
    gen_S(s, a);
    pos = s->pc;
    gen_S(s, pc);
  }
  else {
    gen_B(s, i);
    gen_B(s, (uint8_t)a);
    pos = s->pc;
    gen_S(s, pc);
  }
  return pos;
}