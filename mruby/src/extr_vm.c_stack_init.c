#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {int /*<<< orphan*/ * stack; TYPE_2__* ci; TYPE_2__* cibase; TYPE_2__* ciend; int /*<<< orphan*/ * stbase; int /*<<< orphan*/ * stend; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_5__ {int /*<<< orphan*/  object_class; struct mrb_context* c; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_6__ {int /*<<< orphan*/ * stackent; int /*<<< orphan*/  target_class; } ;
typedef  TYPE_2__ mrb_callinfo ;

/* Variables and functions */
 int CALLINFO_INIT_SIZE ; 
 int STACK_INIT_SIZE ; 
 scalar_t__ mrb_calloc (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
stack_init(mrb_state *mrb)
{
  struct mrb_context *c = mrb->c;

  /* mrb_assert(mrb->stack == NULL); */
  c->stbase = (mrb_value *)mrb_calloc(mrb, STACK_INIT_SIZE, sizeof(mrb_value));
  c->stend = c->stbase + STACK_INIT_SIZE;
  c->stack = c->stbase;

  /* mrb_assert(ci == NULL); */
  c->cibase = (mrb_callinfo *)mrb_calloc(mrb, CALLINFO_INIT_SIZE, sizeof(mrb_callinfo));
  c->ciend = c->cibase + CALLINFO_INIT_SIZE;
  c->ci = c->cibase;
  c->ci->target_class = mrb->object_class;
  c->ci->stackent = c->stack;
}