#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mrb_context {size_t stack; size_t stbase; size_t stend; size_t eidx; int /*<<< orphan*/ * ci; int /*<<< orphan*/ * cibase; int /*<<< orphan*/  status; } ;
struct RObject {int dummy; } ;
struct RHash {int dummy; } ;
struct RFiber {struct mrb_context* cxt; } ;
struct RClass {int dummy; } ;
struct RBasic {int tt; } ;
struct RArray {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_gc ;
typedef  int /*<<< orphan*/  mrb_callinfo ;

/* Variables and functions */
 size_t ARY_LEN (struct RArray*) ; 
 size_t MRB_ENV_STACK_LEN (struct RBasic*) ; 
 int /*<<< orphan*/  MRB_FIBER_TERMINATED ; 
#define  MRB_TT_ARRAY 140 
#define  MRB_TT_CLASS 139 
#define  MRB_TT_DATA 138 
#define  MRB_TT_ENV 137 
#define  MRB_TT_EXCEPTION 136 
#define  MRB_TT_FIBER 135 
#define  MRB_TT_HASH 134 
#define  MRB_TT_ICLASS 133 
#define  MRB_TT_MODULE 132 
#define  MRB_TT_OBJECT 131 
#define  MRB_TT_PROC 130 
#define  MRB_TT_RANGE 129 
#define  MRB_TT_SCLASS 128 
 size_t ci_nregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_mark_children (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct RBasic*) ; 
 size_t mrb_gc_mark_hash_size (int /*<<< orphan*/ *,struct RHash*) ; 
 size_t mrb_gc_mark_iv_size (int /*<<< orphan*/ *,struct RObject*) ; 
 size_t mrb_gc_mark_mt_size (int /*<<< orphan*/ *,struct RClass*) ; 

__attribute__((used)) static size_t
gc_gray_mark(mrb_state *mrb, mrb_gc *gc, struct RBasic *obj)
{
  size_t children = 0;

  gc_mark_children(mrb, gc, obj);

  switch (obj->tt) {
  case MRB_TT_ICLASS:
    children++;
    break;

  case MRB_TT_CLASS:
  case MRB_TT_SCLASS:
  case MRB_TT_MODULE:
    {
      struct RClass *c = (struct RClass*)obj;

      children += mrb_gc_mark_iv_size(mrb, (struct RObject*)obj);
      children += mrb_gc_mark_mt_size(mrb, c);
      children++;
    }
    break;

  case MRB_TT_OBJECT:
  case MRB_TT_DATA:
  case MRB_TT_EXCEPTION:
    children += mrb_gc_mark_iv_size(mrb, (struct RObject*)obj);
    break;

  case MRB_TT_ENV:
    children += MRB_ENV_STACK_LEN(obj);
    break;

  case MRB_TT_FIBER:
    {
      struct mrb_context *c = ((struct RFiber*)obj)->cxt;
      size_t i;
      mrb_callinfo *ci;

      if (!c || c->status == MRB_FIBER_TERMINATED) break;

      /* mark stack */
      i = c->stack - c->stbase;

      if (c->ci) {
        i += ci_nregs(c->ci);
      }
      if (c->stbase + i > c->stend) i = c->stend - c->stbase;
      children += i;

      /* mark ensure stack */
      children += c->eidx;

      /* mark closure */
      if (c->cibase) {
        for (i=0, ci = c->cibase; ci <= c->ci; i++, ci++)
          ;
      }
      children += i;
    }
    break;

  case MRB_TT_ARRAY:
    {
      struct RArray *a = (struct RArray*)obj;
      children += ARY_LEN(a);
    }
    break;

  case MRB_TT_HASH:
    children += mrb_gc_mark_iv_size(mrb, (struct RObject*)obj);
    children += mrb_gc_mark_hash_size(mrb, (struct RHash*)obj);
    break;

  case MRB_TT_PROC:
  case MRB_TT_RANGE:
    children+=2;
    break;

  default:
    break;
  }
  return children;
}