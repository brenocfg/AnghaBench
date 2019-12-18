#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {int dummy; } ;
struct TYPE_10__ {scalar_t__ fshared; } ;
struct TYPE_11__ {TYPE_3__ aux; } ;
struct TYPE_12__ {TYPE_4__ heap; } ;
struct RString {TYPE_5__ as; } ;
struct RRange {int dummy; } ;
struct TYPE_8__ {scalar_t__ env; } ;
struct RProc {TYPE_1__ e; scalar_t__ upper; } ;
struct RObject {int dummy; } ;
struct RHash {int dummy; } ;
struct RFiber {struct mrb_context* cxt; } ;
struct REnv {int /*<<< orphan*/ * stack; TYPE_2__* cxt; } ;
struct RClass {scalar_t__ super; } ;
struct RBasic {int tt; scalar_t__ c; int /*<<< orphan*/  gcnext; } ;
struct RArray {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
struct TYPE_13__ {int /*<<< orphan*/  gray_list; } ;
typedef  TYPE_6__ mrb_gc ;
struct TYPE_9__ {scalar_t__ fib; } ;

/* Variables and functions */
 size_t ARY_LEN (struct RArray*) ; 
 int /*<<< orphan*/ * ARY_PTR (struct RArray*) ; 
 size_t MRB_ENV_STACK_LEN (struct REnv*) ; 
 int /*<<< orphan*/  MRB_ENV_STACK_SHARED_P (struct REnv*) ; 
 int /*<<< orphan*/  MRB_FLAG_TEST (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_FL_CLASS_IS_ORIGIN ; 
#define  MRB_TT_ARRAY 141 
#define  MRB_TT_CLASS 140 
#define  MRB_TT_DATA 139 
#define  MRB_TT_ENV 138 
#define  MRB_TT_EXCEPTION 137 
#define  MRB_TT_FIBER 136 
#define  MRB_TT_HASH 135 
#define  MRB_TT_ICLASS 134 
#define  MRB_TT_MODULE 133 
#define  MRB_TT_OBJECT 132 
#define  MRB_TT_PROC 131 
#define  MRB_TT_RANGE 130 
#define  MRB_TT_SCLASS 129 
#define  MRB_TT_STRING 128 
 int /*<<< orphan*/  RSTR_FSHARED_P (struct RBasic*) ; 
 int /*<<< orphan*/  is_gray (struct RBasic*) ; 
 int /*<<< orphan*/  mark_context (int /*<<< orphan*/ *,struct mrb_context*) ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_mark (int /*<<< orphan*/ *,struct RBasic*) ; 
 int /*<<< orphan*/  mrb_gc_mark_hash (int /*<<< orphan*/ *,struct RHash*) ; 
 int /*<<< orphan*/  mrb_gc_mark_iv (int /*<<< orphan*/ *,struct RObject*) ; 
 int /*<<< orphan*/  mrb_gc_mark_mt (int /*<<< orphan*/ *,struct RClass*) ; 
 int /*<<< orphan*/  mrb_gc_mark_range (int /*<<< orphan*/ *,struct RRange*) ; 
 int /*<<< orphan*/  mrb_gc_mark_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paint_black (struct RBasic*) ; 

__attribute__((used)) static void
gc_mark_children(mrb_state *mrb, mrb_gc *gc, struct RBasic *obj)
{
  mrb_assert(is_gray(obj));
  paint_black(obj);
  gc->gray_list = obj->gcnext;
  mrb_gc_mark(mrb, (struct RBasic*)obj->c);
  switch (obj->tt) {
  case MRB_TT_ICLASS:
    {
      struct RClass *c = (struct RClass*)obj;
      if (MRB_FLAG_TEST(c, MRB_FL_CLASS_IS_ORIGIN))
        mrb_gc_mark_mt(mrb, c);
      mrb_gc_mark(mrb, (struct RBasic*)((struct RClass*)obj)->super);
    }
    break;

  case MRB_TT_CLASS:
  case MRB_TT_MODULE:
  case MRB_TT_SCLASS:
    {
      struct RClass *c = (struct RClass*)obj;

      mrb_gc_mark_mt(mrb, c);
      mrb_gc_mark(mrb, (struct RBasic*)c->super);
    }
    /* fall through */

  case MRB_TT_OBJECT:
  case MRB_TT_DATA:
  case MRB_TT_EXCEPTION:
    mrb_gc_mark_iv(mrb, (struct RObject*)obj);
    break;

  case MRB_TT_PROC:
    {
      struct RProc *p = (struct RProc*)obj;

      mrb_gc_mark(mrb, (struct RBasic*)p->upper);
      mrb_gc_mark(mrb, (struct RBasic*)p->e.env);
    }
    break;

  case MRB_TT_ENV:
    {
      struct REnv *e = (struct REnv*)obj;
      mrb_int i, len;

      if (MRB_ENV_STACK_SHARED_P(e) && e->cxt && e->cxt->fib) {
        mrb_gc_mark(mrb, (struct RBasic*)e->cxt->fib);
      }
      len = MRB_ENV_STACK_LEN(e);
      for (i=0; i<len; i++) {
        mrb_gc_mark_value(mrb, e->stack[i]);
      }
    }
    break;

  case MRB_TT_FIBER:
    {
      struct mrb_context *c = ((struct RFiber*)obj)->cxt;

      if (c) mark_context(mrb, c);
    }
    break;

  case MRB_TT_ARRAY:
    {
      struct RArray *a = (struct RArray*)obj;
      size_t i, e;

      for (i=0,e=ARY_LEN(a); i<e; i++) {
        mrb_gc_mark_value(mrb, ARY_PTR(a)[i]);
      }
    }
    break;

  case MRB_TT_HASH:
    mrb_gc_mark_iv(mrb, (struct RObject*)obj);
    mrb_gc_mark_hash(mrb, (struct RHash*)obj);
    break;

  case MRB_TT_STRING:
    if (RSTR_FSHARED_P(obj)) {
      struct RString *s = (struct RString*)obj;
      mrb_gc_mark(mrb, (struct RBasic*)s->as.heap.aux.fshared);
    }
    break;

  case MRB_TT_RANGE:
    mrb_gc_mark_range(mrb, (struct RRange*)obj);
    break;

  default:
    break;
  }
}