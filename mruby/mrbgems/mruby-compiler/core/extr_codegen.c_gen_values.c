#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* cdr; TYPE_3__* car; } ;
typedef  TYPE_1__ node ;
typedef  int /*<<< orphan*/  codegen_scope ;
struct TYPE_5__ {int /*<<< orphan*/  car; struct TYPE_5__* cdr; } ;

/* Variables and functions */
 int CALL_MAXARGS ; 
 scalar_t__ NODE_ARRAY ; 
 scalar_t__ NODE_SPLAT ; 
 int NOVAL ; 
 int /*<<< orphan*/  OP_ARRAY ; 
 int /*<<< orphan*/  OP_ARYCAT ; 
 int /*<<< orphan*/  OP_ARYPUSH ; 
 int /*<<< orphan*/  OP_LOADNIL ; 
 int VAL ; 
 int /*<<< orphan*/  codegen (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  cursp () ; 
 int /*<<< orphan*/  genop_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genop_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop () ; 
 int /*<<< orphan*/  pop_n (int) ; 
 int /*<<< orphan*/  push () ; 

__attribute__((used)) static int
gen_values(codegen_scope *s, node *t, int val, int extra)
{
  int n = 0;
  int is_splat;

  while (t) {
    is_splat = nint(t->car->car) == NODE_SPLAT; /* splat mode */
    if (
      n+extra >= CALL_MAXARGS - 1 /* need to subtract one because vm.c expects an array if n == CALL_MAXARGS */
      || is_splat) {
      if (val) {
        if (is_splat && n == 0 && nint(t->car->cdr->car) == NODE_ARRAY) {
          codegen(s, t->car->cdr, VAL);
          pop();
        }
        else {
          pop_n(n);
          if (n == 0 && is_splat) {
            genop_1(s, OP_LOADNIL, cursp());
          }
          else {
            genop_2(s, OP_ARRAY, cursp(), n);
          }
          push();
          codegen(s, t->car, VAL);
          pop(); pop();
          if (is_splat) {
            genop_1(s, OP_ARYCAT, cursp());
          }
          else {
            genop_1(s, OP_ARYPUSH, cursp());
          }
        }
        t = t->cdr;
        while (t) {
          push();
          codegen(s, t->car, VAL);
          pop(); pop();
          if (nint(t->car->car) == NODE_SPLAT) {
            genop_1(s, OP_ARYCAT, cursp());
          }
          else {
            genop_1(s, OP_ARYPUSH, cursp());
          }
          t = t->cdr;
        }
      }
      else {
        while (t) {
          codegen(s, t->car, NOVAL);
          t = t->cdr;
        }
      }
      return -1;
    }
    /* normal (no splat) mode */
    codegen(s, t->car, val);
    n++;
    t = t->cdr;
  }
  return n;
}