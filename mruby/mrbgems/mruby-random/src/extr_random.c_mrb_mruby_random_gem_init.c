#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  rand_state ;
struct TYPE_9__ {int /*<<< orphan*/  object_class; struct RClass* kernel_module; struct RClass* array_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int ISTRUCT_DATA_SIZE ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_ISTRUCT ; 
 int /*<<< orphan*/  mrb_ary_sample ; 
 int /*<<< orphan*/  mrb_ary_shuffle ; 
 int /*<<< orphan*/  mrb_ary_shuffle_bang ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_const_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_obj_new (TYPE_1__*,struct RClass*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_obj_value (struct RClass*) ; 
 int /*<<< orphan*/  random_f_rand ; 
 int /*<<< orphan*/  random_f_srand ; 
 int /*<<< orphan*/  random_m_init ; 
 int /*<<< orphan*/  random_m_rand ; 
 int /*<<< orphan*/  random_m_srand ; 

void mrb_mruby_random_gem_init(mrb_state *mrb)
{
  struct RClass *random;
  struct RClass *array = mrb->array_class;

  mrb_assert(sizeof(rand_state) <= ISTRUCT_DATA_SIZE);

  mrb_define_method(mrb, mrb->kernel_module, "rand", random_f_rand, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, mrb->kernel_module, "srand", random_f_srand, MRB_ARGS_OPT(1));

  random = mrb_define_class(mrb, "Random", mrb->object_class);
  MRB_SET_INSTANCE_TT(random, MRB_TT_ISTRUCT);
  mrb_define_class_method(mrb, random, "rand", random_f_rand, MRB_ARGS_OPT(1));
  mrb_define_class_method(mrb, random, "srand", random_f_srand, MRB_ARGS_OPT(1));

  mrb_define_method(mrb, random, "initialize", random_m_init, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, random, "rand", random_m_rand, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, random, "srand", random_m_srand, MRB_ARGS_OPT(1));

  mrb_define_method(mrb, array, "shuffle", mrb_ary_shuffle, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, array, "shuffle!", mrb_ary_shuffle_bang, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, array, "sample", mrb_ary_sample, MRB_ARGS_OPT(2));

  mrb_const_set(mrb, mrb_obj_value(random), mrb_intern_lit(mrb, "DEFAULT"),
          mrb_obj_new(mrb, random, 0, NULL));
}