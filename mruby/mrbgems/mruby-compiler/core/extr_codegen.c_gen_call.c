#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_10__* cdr; TYPE_10__* car; } ;
typedef  TYPE_2__ node ;
typedef  scalar_t__ mrb_sym ;
typedef  int mrb_int ;
struct TYPE_21__ {int /*<<< orphan*/  mrb; } ;
typedef  TYPE_3__ codegen_scope ;
struct TYPE_19__ {TYPE_2__* car; } ;
struct TYPE_18__ {TYPE_1__* cdr; int /*<<< orphan*/  car; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ARYPUSH ; 
 int /*<<< orphan*/  OP_DIV ; 
 int /*<<< orphan*/  OP_EQ ; 
 int /*<<< orphan*/  OP_GE ; 
 int /*<<< orphan*/  OP_GT ; 
 int /*<<< orphan*/  OP_JMPNIL ; 
 int /*<<< orphan*/  OP_LE ; 
 int /*<<< orphan*/  OP_LT ; 
 int /*<<< orphan*/  OP_MUL ; 
 int /*<<< orphan*/  OP_SEND ; 
 int /*<<< orphan*/  OP_SENDB ; 
 int /*<<< orphan*/  OP_SENDV ; 
 int /*<<< orphan*/  OP_SENDVB ; 
 int /*<<< orphan*/  OP_SUB ; 
 int /*<<< orphan*/  VAL ; 
 int /*<<< orphan*/  codegen (TYPE_3__*,TYPE_10__*,int /*<<< orphan*/ ) ; 
 int cursp () ; 
 int /*<<< orphan*/  dispatch (TYPE_3__*,int) ; 
 int /*<<< orphan*/  gen_addsub (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_move (TYPE_3__*,int,int,int) ; 
 int gen_values (TYPE_3__*,TYPE_10__*,int /*<<< orphan*/ ,int) ; 
 int genjmp2 (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genop_1 (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  genop_2 (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  genop_3 (TYPE_3__*,int /*<<< orphan*/ ,int,int,int) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int new_sym (TYPE_3__*,scalar_t__) ; 
 scalar_t__ nsym (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 

__attribute__((used)) static void
gen_call(codegen_scope *s, node *tree, mrb_sym name, int sp, int val, int safe)
{
  mrb_sym sym = name ? name : nsym(tree->cdr->car);
  int skip = 0;
  int n = 0, noop = 0, sendv = 0, blk = 0;

  codegen(s, tree->car, VAL); /* receiver */
  if (safe) {
    int recv = cursp()-1;
    gen_move(s, cursp(), recv, 1);
    skip = genjmp2(s, OP_JMPNIL, cursp(), 0, val);
  }
  tree = tree->cdr->cdr->car;
  if (tree) {
    n = gen_values(s, tree->car, VAL, sp?1:0);
    if (n < 0) {
      n = noop = sendv = 1;
      push();
    }
  }
  if (sp) {                     /* last argument pushed (attr=) */
    if (sendv) {
      gen_move(s, cursp(), sp, 0);
      pop();
      genop_1(s, OP_ARYPUSH, cursp());
      push();
    }
    else {
      gen_move(s, cursp(), sp, 0);
      push();
      n++;
    }
  }
  if (tree && tree->cdr) {
    noop = 1;
    codegen(s, tree->cdr, VAL);
    pop();
    blk = 1;
  }
  push();pop();
  pop_n(n+1);
  {
    mrb_int symlen;
    const char *symname = mrb_sym_name_len(s->mrb, sym, &symlen);

    if (!noop && symlen == 1 && symname[0] == '+' && n == 1)  {
      gen_addsub(s, OP_ADD, cursp());
    }
    else if (!noop && symlen == 1 && symname[0] == '-' && n == 1)  {
      gen_addsub(s, OP_SUB, cursp());
    }
    else if (!noop && symlen == 1 && symname[0] == '*' && n == 1)  {
      genop_1(s, OP_MUL, cursp());
    }
    else if (!noop && symlen == 1 && symname[0] == '/' && n == 1)  {
      genop_1(s, OP_DIV, cursp());
    }
    else if (!noop && symlen == 1 && symname[0] == '<' && n == 1)  {
      genop_1(s, OP_LT, cursp());
    }
    else if (!noop && symlen == 2 && symname[0] == '<' && symname[1] == '=' && n == 1)  {
      genop_1(s, OP_LE, cursp());
    }
    else if (!noop && symlen == 1 && symname[0] == '>' && n == 1)  {
      genop_1(s, OP_GT, cursp());
    }
    else if (!noop && symlen == 2 && symname[0] == '>' && symname[1] == '=' && n == 1)  {
      genop_1(s, OP_GE, cursp());
    }
    else if (!noop && symlen == 2 && symname[0] == '=' && symname[1] == '=' && n == 1)  {
      genop_1(s, OP_EQ, cursp());
    }
    else {
      int idx = new_sym(s, sym);

      if (sendv) {
        genop_2(s, blk ? OP_SENDVB : OP_SENDV, cursp(), idx);
      }
      else {
        genop_3(s, blk ? OP_SENDB : OP_SEND, cursp(), idx, n);
      }
    }
  }
  if (safe) {
    dispatch(s, skip);
  }
  if (val) {
    push();
  }
}