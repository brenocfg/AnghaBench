#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* cdr; struct TYPE_4__* car; } ;
typedef  TYPE_1__ node ;
typedef  int /*<<< orphan*/  codegen_scope ;

/* Variables and functions */
 int /*<<< orphan*/  NOVAL ; 
 int /*<<< orphan*/  OP_APOST ; 
 int /*<<< orphan*/  OP_AREF ; 
 int cursp () ; 
 int /*<<< orphan*/  gen_assignment (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_move (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  genop_3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 
 int /*<<< orphan*/  push_n (int) ; 

__attribute__((used)) static void
gen_vmassignment(codegen_scope *s, node *tree, int rhs, int val)
{
  int n = 0, post = 0;
  node *t, *p;

  if (tree->car) {              /* pre */
    t = tree->car;
    n = 0;
    while (t) {
      int sp = cursp();

      genop_3(s, OP_AREF, sp, rhs, n);
      push();
      gen_assignment(s, t->car, sp, NOVAL);
      pop();
      n++;
      t = t->cdr;
    }
  }
  t = tree->cdr;
  if (t) {
    if (t->cdr) {               /* post count */
      p = t->cdr->car;
      while (p) {
        post++;
        p = p->cdr;
      }
    }
    gen_move(s, cursp(), rhs, val);
    push_n(post+1);
    pop_n(post+1);
    genop_3(s, OP_APOST, cursp(), n, post);
    n = 1;
    if (t->car && t->car != (node*)-1) { /* rest */
      gen_assignment(s, t->car, cursp(), NOVAL);
    }
    if (t->cdr && t->cdr->car) {
      t = t->cdr->car;
      while (t) {
        gen_assignment(s, t->car, cursp()+n, NOVAL);
        t = t->cdr;
        n++;
      }
    }
    if (val) {
      gen_move(s, cursp(), rhs, 0);
    }
  }
}