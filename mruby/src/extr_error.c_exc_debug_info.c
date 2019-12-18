#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct RObject {int dummy; } ;
struct TYPE_19__ {TYPE_1__* c; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_20__ {int iseq; } ;
typedef  TYPE_4__ mrb_irep ;
typedef  int /*<<< orphan*/  mrb_code ;
struct TYPE_21__ {int /*<<< orphan*/ * pc; TYPE_15__* proc; int /*<<< orphan*/ * err; } ;
typedef  TYPE_5__ mrb_callinfo ;
typedef  int int32_t ;
struct TYPE_18__ {TYPE_4__* irep; } ;
struct TYPE_17__ {TYPE_5__* cibase; TYPE_5__* ci; } ;
struct TYPE_16__ {TYPE_2__ body; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (TYPE_15__*) ; 
 char* mrb_debug_get_filename (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/  const*) ; 
 int mrb_debug_get_line (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int const) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_3__*,char*) ; 
 scalar_t__ mrb_obj_iv_defined (TYPE_3__*,struct RObject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_iv_set (TYPE_3__*,struct RObject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (TYPE_3__*,char const*) ; 

__attribute__((used)) static void
exc_debug_info(mrb_state *mrb, struct RObject *exc)
{
  mrb_callinfo *ci = mrb->c->ci;
  const mrb_code *pc = ci->pc;

  if (mrb_obj_iv_defined(mrb, exc, mrb_intern_lit(mrb, "file"))) return;
  while (ci >= mrb->c->cibase) {
    const mrb_code *err = ci->err;

    if (!err && pc) err = pc - 1;
    if (err && ci->proc && !MRB_PROC_CFUNC_P(ci->proc)) {
      mrb_irep *irep = ci->proc->body.irep;

      int32_t const line = mrb_debug_get_line(mrb, irep, err - irep->iseq);
      char const* file = mrb_debug_get_filename(mrb, irep, err - irep->iseq);
      if (line != -1 && file) {
        mrb_obj_iv_set(mrb, exc, mrb_intern_lit(mrb, "file"), mrb_str_new_cstr(mrb, file));
        mrb_obj_iv_set(mrb, exc, mrb_intern_lit(mrb, "line"), mrb_fixnum_value(line));
        return;
      }
    }
    pc = ci->pc;
    ci--;
  }
}