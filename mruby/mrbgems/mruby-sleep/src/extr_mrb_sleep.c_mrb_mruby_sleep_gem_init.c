#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kernel_module; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_f_sleep ; 
 int /*<<< orphan*/  mrb_f_usleep ; 

void
mrb_mruby_sleep_gem_init(mrb_state *mrb)
{
    mrb_define_method(mrb, mrb->kernel_module, "sleep",   mrb_f_sleep,   MRB_ARGS_REQ(1));
    mrb_define_method(mrb, mrb->kernel_module, "usleep",  mrb_f_usleep,  MRB_ARGS_REQ(1));
}