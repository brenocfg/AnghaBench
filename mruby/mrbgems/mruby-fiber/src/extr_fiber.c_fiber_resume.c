#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_9__ {TYPE_2__* c; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;
struct TYPE_8__ {TYPE_1__* ci; } ;
struct TYPE_7__ {scalar_t__ acc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  fiber_switch (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_3__*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
fiber_resume(mrb_state *mrb, mrb_value self)
{
  mrb_value *a;
  mrb_int len;
  mrb_bool vmexec = FALSE;

  mrb_get_args(mrb, "*!", &a, &len);
  if (mrb->c->ci->acc < 0) {
    vmexec = TRUE;
  }
  return fiber_switch(mrb, self, len, a, TRUE, vmexec);
}