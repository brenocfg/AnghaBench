#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_10__ {TYPE_2__* c; } ;
typedef  TYPE_3__ mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;
struct TYPE_9__ {TYPE_1__* ci; } ;
struct TYPE_8__ {struct RClass* target_class; } ;

/* Variables and functions */
#define  MRB_TT_FIXNUM 130 
#define  MRB_TT_FLOAT 129 
#define  MRB_TT_SYMBOL 128 
 struct RClass* mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (TYPE_3__*,char*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_singleton_class (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int mrb_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_yield_cont (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static mrb_value
mrb_obj_instance_exec(mrb_state *mrb, mrb_value self)
{
  const mrb_value *argv;
  mrb_int argc;
  mrb_value blk;
  struct RClass *c;

  mrb_get_args(mrb, "*&!", &argv, &argc, &blk);

  switch (mrb_type(self)) {
  case MRB_TT_SYMBOL:
  case MRB_TT_FIXNUM:
#ifndef MRB_WITHOUT_FLOAT
  case MRB_TT_FLOAT:
#endif
    c = NULL;
    break;
  default:
    c = mrb_class_ptr(mrb_singleton_class(mrb, self));
    break;
  }
  mrb->c->ci->target_class = c;
  return mrb_yield_cont(mrb, blk, self, argc, argv);
}