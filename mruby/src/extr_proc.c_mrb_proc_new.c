#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * irep; } ;
struct TYPE_9__ {struct RClass* target_class; } ;
struct RProc {TYPE_2__ body; TYPE_1__ e; scalar_t__ upper; } ;
struct RClass {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  proc_class; TYPE_3__* c; } ;
typedef  TYPE_4__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
struct TYPE_13__ {scalar_t__ proc; struct RClass* target_class; } ;
typedef  TYPE_5__ mrb_callinfo ;
struct TYPE_11__ {TYPE_5__* ci; } ;

/* Variables and functions */
 struct RClass* MRB_PROC_TARGET_CLASS (scalar_t__) ; 
 int /*<<< orphan*/  MRB_TT_PROC ; 
 int /*<<< orphan*/  mrb_irep_incref (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_obj_alloc (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct RProc*
mrb_proc_new(mrb_state *mrb, mrb_irep *irep)
{
  struct RProc *p;
  mrb_callinfo *ci = mrb->c->ci;

  p = (struct RProc*)mrb_obj_alloc(mrb, MRB_TT_PROC, mrb->proc_class);
  if (ci) {
    struct RClass *tc = NULL;

    if (ci->proc) {
      tc = MRB_PROC_TARGET_CLASS(ci->proc);
    }
    if (tc == NULL) {
      tc = ci->target_class;
    }
    p->upper = ci->proc;
    p->e.target_class = tc;
  }
  p->body.irep = irep;
  mrb_irep_incref(mrb, irep);

  return p;
}