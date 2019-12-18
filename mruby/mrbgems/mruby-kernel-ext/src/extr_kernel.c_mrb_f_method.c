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
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_6__ {TYPE_1__* c; } ;
typedef  TYPE_2__ mrb_state ;
struct TYPE_7__ {scalar_t__ mid; } ;
typedef  TYPE_3__ mrb_callinfo ;
struct TYPE_5__ {TYPE_3__* ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_symbol_value (scalar_t__) ; 

__attribute__((used)) static mrb_value
mrb_f_method(mrb_state *mrb, mrb_value self)
{
  mrb_callinfo *ci = mrb->c->ci;
  ci--;
  if (ci->mid)
    return mrb_symbol_value(ci->mid);
  else
    return mrb_nil_value();
}