#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {int /*<<< orphan*/  status; struct RFiber* fib; TYPE_5__* ci; int /*<<< orphan*/ * stack; TYPE_5__* cibase; TYPE_5__* ciend; int /*<<< orphan*/ * stbase; int /*<<< orphan*/ * stend; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {TYPE_2__* irep; } ;
struct RProc {TYPE_3__ body; } ;
struct RFiber {struct mrb_context* cxt; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_15__ {TYPE_1__* c; } ;
typedef  TYPE_4__ mrb_state ;
struct TYPE_16__ {int /*<<< orphan*/  pc; struct RProc* proc; int /*<<< orphan*/  target_class; int /*<<< orphan*/ * stackent; } ;
typedef  TYPE_5__ mrb_callinfo ;
struct TYPE_13__ {size_t nregs; int /*<<< orphan*/  iseq; } ;
struct TYPE_12__ {int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_FIBER_ERROR ; 
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 int FIBER_CI_INIT_SIZE ; 
 size_t FIBER_STACK_INIT_SIZE ; 
 int /*<<< orphan*/  MRB_FIBER_CREATED ; 
 scalar_t__ MRB_PROC_CFUNC_P (struct RProc*) ; 
 int /*<<< orphan*/  MRB_PROC_TARGET_CLASS (struct RProc*) ; 
 int /*<<< orphan*/  SET_NIL_VALUE (int /*<<< orphan*/ ) ; 
 struct RFiber* fiber_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ mrb_calloc (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  mrb_field_write_barrier (TYPE_4__*,struct RBasic*,struct RBasic*) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_4__*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_malloc (TYPE_4__*,size_t) ; 
 scalar_t__ mrb_obj_ptr (int /*<<< orphan*/ ) ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
fiber_init(mrb_state *mrb, mrb_value self)
{
  static const struct mrb_context mrb_context_zero = { 0 };
  struct RFiber *f = fiber_ptr(self);
  struct mrb_context *c;
  struct RProc *p;
  mrb_callinfo *ci;
  mrb_value blk;
  size_t slen;

  mrb_get_args(mrb, "&!", &blk);

  if (f->cxt) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot initialize twice");
  }
  p = mrb_proc_ptr(blk);
  if (MRB_PROC_CFUNC_P(p)) {
    mrb_raise(mrb, E_FIBER_ERROR, "tried to create Fiber from C defined method");
  }

  c = (struct mrb_context*)mrb_malloc(mrb, sizeof(struct mrb_context));
  *c = mrb_context_zero;
  f->cxt = c;

  /* initialize VM stack */
  slen = FIBER_STACK_INIT_SIZE;
  if (p->body.irep->nregs > slen) {
    slen += p->body.irep->nregs;
  }
  c->stbase = (mrb_value *)mrb_malloc(mrb, slen*sizeof(mrb_value));
  c->stend = c->stbase + slen;
  c->stack = c->stbase;

#ifdef MRB_NAN_BOXING
  {
    mrb_value *p = c->stbase;
    mrb_value *pend = c->stend;

    while (p < pend) {
      SET_NIL_VALUE(*p);
      p++;
    }
  }
#else
  memset(c->stbase, 0, slen * sizeof(mrb_value));
#endif

  /* copy receiver from a block */
  c->stack[0] = mrb->c->stack[0];

  /* initialize callinfo stack */
  c->cibase = (mrb_callinfo *)mrb_calloc(mrb, FIBER_CI_INIT_SIZE, sizeof(mrb_callinfo));
  c->ciend = c->cibase + FIBER_CI_INIT_SIZE;
  c->ci = c->cibase;
  c->ci->stackent = c->stack;

  /* adjust return callinfo */
  ci = c->ci;
  ci->target_class = MRB_PROC_TARGET_CLASS(p);
  ci->proc = p;
  mrb_field_write_barrier(mrb, (struct RBasic*)mrb_obj_ptr(self), (struct RBasic*)p);
  ci->pc = p->body.irep->iseq;
  ci[1] = ci[0];
  c->ci++;                      /* push dummy callinfo */

  c->fib = f;
  c->status = MRB_FIBER_CREATED;

  return self;
}