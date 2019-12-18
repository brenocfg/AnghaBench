#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct RClass {int dummy; } ;
struct TYPE_7__ {struct RClass* kernel_module; int /*<<< orphan*/  object_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int) ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  mrb_any_to_s ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RClass* mrb_define_module (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  mrb_equal_m ; 
 int /*<<< orphan*/  mrb_f_block_given_p_m ; 
 int /*<<< orphan*/  mrb_f_raise ; 
 int /*<<< orphan*/  mrb_false ; 
 int /*<<< orphan*/  mrb_include_module (TYPE_1__*,int /*<<< orphan*/ ,struct RClass*) ; 
 int /*<<< orphan*/  mrb_obj_ceqq ; 
 int /*<<< orphan*/  mrb_obj_class_m ; 
 int /*<<< orphan*/  mrb_obj_clone ; 
 int /*<<< orphan*/  mrb_obj_dup ; 
 int /*<<< orphan*/  mrb_obj_equal_m ; 
 int /*<<< orphan*/  mrb_obj_extend_m ; 
 int /*<<< orphan*/  mrb_obj_freeze ; 
 int /*<<< orphan*/  mrb_obj_frozen ; 
 int /*<<< orphan*/  mrb_obj_hash ; 
 int /*<<< orphan*/  mrb_obj_id_m ; 
 int /*<<< orphan*/  mrb_obj_init_copy ; 
 int /*<<< orphan*/  mrb_obj_inspect ; 
 int /*<<< orphan*/  mrb_obj_is_kind_of_m ; 
 int /*<<< orphan*/  mrb_obj_missing ; 
 int /*<<< orphan*/  mrb_obj_remove_instance_variable ; 
 int /*<<< orphan*/  mrb_to_int ; 
 int /*<<< orphan*/  mrb_to_str ; 
 int /*<<< orphan*/  obj_is_instance_of ; 
 int /*<<< orphan*/  obj_respond_to ; 

void
mrb_init_kernel(mrb_state *mrb)
{
  struct RClass *krn;

  mrb->kernel_module = krn = mrb_define_module(mrb, "Kernel");                                                    /* 15.3.1 */
  mrb_define_class_method(mrb, krn, "block_given?",         mrb_f_block_given_p_m,           MRB_ARGS_NONE());    /* 15.3.1.2.2  */
  mrb_define_class_method(mrb, krn, "iterator?",            mrb_f_block_given_p_m,           MRB_ARGS_NONE());    /* 15.3.1.2.5  */
;     /* 15.3.1.2.11 */
  mrb_define_class_method(mrb, krn, "raise",                mrb_f_raise,                     MRB_ARGS_OPT(2));    /* 15.3.1.2.12 */


  mrb_define_method(mrb, krn, "===",                        mrb_equal_m,                     MRB_ARGS_REQ(1));    /* 15.3.1.3.2  */
  mrb_define_method(mrb, krn, "block_given?",               mrb_f_block_given_p_m,           MRB_ARGS_NONE());    /* 15.3.1.3.6  */
  mrb_define_method(mrb, krn, "class",                      mrb_obj_class_m,                 MRB_ARGS_NONE());    /* 15.3.1.3.7  */
  mrb_define_method(mrb, krn, "clone",                      mrb_obj_clone,                   MRB_ARGS_NONE());    /* 15.3.1.3.8  */
  mrb_define_method(mrb, krn, "dup",                        mrb_obj_dup,                     MRB_ARGS_NONE());    /* 15.3.1.3.9  */
  mrb_define_method(mrb, krn, "eql?",                       mrb_obj_equal_m,                 MRB_ARGS_REQ(1));    /* 15.3.1.3.10 */
  mrb_define_method(mrb, krn, "extend",                     mrb_obj_extend_m,                MRB_ARGS_ANY());     /* 15.3.1.3.13 */
  mrb_define_method(mrb, krn, "freeze",                     mrb_obj_freeze,                  MRB_ARGS_NONE());
  mrb_define_method(mrb, krn, "frozen?",                    mrb_obj_frozen,                  MRB_ARGS_NONE());
  mrb_define_method(mrb, krn, "hash",                       mrb_obj_hash,                    MRB_ARGS_NONE());    /* 15.3.1.3.15 */
  mrb_define_method(mrb, krn, "initialize_copy",            mrb_obj_init_copy,               MRB_ARGS_REQ(1));    /* 15.3.1.3.16 */
  mrb_define_method(mrb, krn, "inspect",                    mrb_obj_inspect,                 MRB_ARGS_NONE());    /* 15.3.1.3.17 */
  mrb_define_method(mrb, krn, "instance_of?",               obj_is_instance_of,              MRB_ARGS_REQ(1));    /* 15.3.1.3.19 */

  mrb_define_method(mrb, krn, "is_a?",                      mrb_obj_is_kind_of_m,            MRB_ARGS_REQ(1));    /* 15.3.1.3.24 */
  mrb_define_method(mrb, krn, "iterator?",                  mrb_f_block_given_p_m,           MRB_ARGS_NONE());    /* 15.3.1.3.25 */
  mrb_define_method(mrb, krn, "kind_of?",                   mrb_obj_is_kind_of_m,            MRB_ARGS_REQ(1));    /* 15.3.1.3.26 */
  mrb_define_method(mrb, krn, "method_missing",             mrb_obj_missing,                 MRB_ARGS_ANY());     /* 15.3.1.3.30 */
  mrb_define_method(mrb, krn, "nil?",                       mrb_false,                       MRB_ARGS_NONE());    /* 15.3.1.3.32 */
  mrb_define_method(mrb, krn, "object_id",                  mrb_obj_id_m,                    MRB_ARGS_NONE());    /* 15.3.1.3.33 */
  mrb_define_method(mrb, krn, "raise",                      mrb_f_raise,                     MRB_ARGS_ANY());     /* 15.3.1.3.40 */
  mrb_define_method(mrb, krn, "remove_instance_variable",   mrb_obj_remove_instance_variable,MRB_ARGS_REQ(1));    /* 15.3.1.3.41 */
  mrb_define_method(mrb, krn, "respond_to?",                obj_respond_to,                  MRB_ARGS_ARG(1,1));     /* 15.3.1.3.43 */
  mrb_define_method(mrb, krn, "to_s",                       mrb_any_to_s,                    MRB_ARGS_NONE());    /* 15.3.1.3.46 */
  mrb_define_method(mrb, krn, "__case_eqq",                 mrb_obj_ceqq,                    MRB_ARGS_REQ(1));    /* internal */
  mrb_define_method(mrb, krn, "__to_int",                   mrb_to_int,                      MRB_ARGS_NONE()); /* internal */
  mrb_define_method(mrb, krn, "__to_str",                   mrb_to_str,                      MRB_ARGS_NONE()); /* internal */

  mrb_include_module(mrb, mrb->object_class, mrb->kernel_module);
}