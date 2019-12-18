#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct REnv {int /*<<< orphan*/ * stack; } ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_6__ {TYPE_1__* c; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_7__ {int /*<<< orphan*/ * stackent; scalar_t__ proc; struct REnv* env; } ;
typedef  TYPE_3__ mrb_callinfo ;
struct TYPE_5__ {TYPE_3__* ci; TYPE_3__* cibase; } ;

/* Variables and functions */
 scalar_t__ MRB_ENV_STACK_SHARED_P (struct REnv*) ; 
 struct REnv* MRB_PROC_ENV (scalar_t__) ; 
 scalar_t__ MRB_PROC_ENV_P (scalar_t__) ; 

__attribute__((used)) static inline void
envadjust(mrb_state *mrb, mrb_value *oldbase, mrb_value *newbase, size_t oldsize)
{
  mrb_callinfo *ci = mrb->c->cibase;

  if (newbase == oldbase) return;
  while (ci <= mrb->c->ci) {
    struct REnv *e = ci->env;
    mrb_value *st;

    if (e && MRB_ENV_STACK_SHARED_P(e) &&
        (st = e->stack) && oldbase <= st && st < oldbase+oldsize) {
      ptrdiff_t off = e->stack - oldbase;

      e->stack = newbase + off;
    }

    if (ci->proc && MRB_PROC_ENV_P(ci->proc) && ci->env != MRB_PROC_ENV(ci->proc)) {
      e = MRB_PROC_ENV(ci->proc);

      if (e && MRB_ENV_STACK_SHARED_P(e) &&
          (st = e->stack) && oldbase <= st && st < oldbase+oldsize) {
        ptrdiff_t off = e->stack - oldbase;

        e->stack = newbase + off;
      }
    }

    ci->stackent = newbase + (ci->stackent - oldbase);
    ci++;
  }
}