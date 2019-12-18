#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct REnv {TYPE_1__* cxt; int /*<<< orphan*/  stack; int /*<<< orphan*/  mid; } ;
struct TYPE_7__ {TYPE_1__* c; } ;
typedef  TYPE_2__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
struct TYPE_8__ {int argc; int /*<<< orphan*/  mid; } ;
typedef  TYPE_3__ mrb_callinfo ;
struct TYPE_6__ {int /*<<< orphan*/  stack; TYPE_3__* ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ENV_SET_BIDX (struct REnv*,int) ; 
 int /*<<< orphan*/  MRB_ENV_SET_STACK_LEN (struct REnv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_ENV ; 
 scalar_t__ mrb_obj_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct REnv*
env_new(mrb_state *mrb, mrb_int nlocals)
{
  struct REnv *e;
  mrb_callinfo *ci = mrb->c->ci;
  int bidx;

  e = (struct REnv*)mrb_obj_alloc(mrb, MRB_TT_ENV, NULL);
  MRB_ENV_SET_STACK_LEN(e, nlocals);
  bidx = ci->argc;
  if (ci->argc < 0) bidx = 2;
  else bidx += 1;
  MRB_ENV_SET_BIDX(e, bidx);
  e->mid = ci->mid;
  e->stack = mrb->c->stack;
  e->cxt = mrb->c;

  return e;
}