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
struct TYPE_7__ {int /*<<< orphan*/  object_class; struct RClass* array_class; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ARGS_ANY () ; 
 int /*<<< orphan*/  MRB_ARGS_ARG (int,int) ; 
 int /*<<< orphan*/  MRB_ARGS_NONE () ; 
 int /*<<< orphan*/  MRB_ARGS_OPT (int) ; 
 int /*<<< orphan*/  MRB_ARGS_REQ (int) ; 
 int /*<<< orphan*/  MRB_SET_INSTANCE_TT (struct RClass*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MRB_TT_ARRAY ; 
 int /*<<< orphan*/  init_ary_each (TYPE_1__*,struct RClass*) ; 
 int /*<<< orphan*/  mrb_ary_aget ; 
 int /*<<< orphan*/  mrb_ary_aset ; 
 int /*<<< orphan*/  mrb_ary_clear_m ; 
 int /*<<< orphan*/  mrb_ary_cmp ; 
 int /*<<< orphan*/  mrb_ary_concat_m ; 
 int /*<<< orphan*/  mrb_ary_delete_at ; 
 int /*<<< orphan*/  mrb_ary_empty_p ; 
 int /*<<< orphan*/  mrb_ary_eq ; 
 int /*<<< orphan*/  mrb_ary_first ; 
 int /*<<< orphan*/  mrb_ary_index_m ; 
 int /*<<< orphan*/  mrb_ary_join_m ; 
 int /*<<< orphan*/  mrb_ary_last ; 
 int /*<<< orphan*/  mrb_ary_plus ; 
 int /*<<< orphan*/  mrb_ary_pop ; 
 int /*<<< orphan*/  mrb_ary_push_m ; 
 int /*<<< orphan*/  mrb_ary_replace_m ; 
 int /*<<< orphan*/  mrb_ary_reverse ; 
 int /*<<< orphan*/  mrb_ary_reverse_bang ; 
 int /*<<< orphan*/  mrb_ary_rindex_m ; 
 int /*<<< orphan*/  mrb_ary_s_create ; 
 int /*<<< orphan*/  mrb_ary_shift ; 
 int /*<<< orphan*/  mrb_ary_size ; 
 int /*<<< orphan*/  mrb_ary_svalue ; 
 int /*<<< orphan*/  mrb_ary_times ; 
 int /*<<< orphan*/  mrb_ary_unshift_m ; 
 struct RClass* mrb_define_class (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_class_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method (TYPE_1__*,struct RClass*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_init_array(mrb_state *mrb)
{
  struct RClass *a;

  mrb->array_class = a = mrb_define_class(mrb, "Array", mrb->object_class);              /* 15.2.12 */
  MRB_SET_INSTANCE_TT(a, MRB_TT_ARRAY);

  mrb_define_class_method(mrb, a, "[]",        mrb_ary_s_create,     MRB_ARGS_ANY());    /* 15.2.12.4.1 */

  mrb_define_method(mrb, a, "+",               mrb_ary_plus,         MRB_ARGS_REQ(1));   /* 15.2.12.5.1  */
  mrb_define_method(mrb, a, "*",               mrb_ary_times,        MRB_ARGS_REQ(1));   /* 15.2.12.5.2  */
  mrb_define_method(mrb, a, "<<",              mrb_ary_push_m,       MRB_ARGS_REQ(1));   /* 15.2.12.5.3  */
  mrb_define_method(mrb, a, "[]",              mrb_ary_aget,         MRB_ARGS_ARG(1,1)); /* 15.2.12.5.4  */
  mrb_define_method(mrb, a, "[]=",             mrb_ary_aset,         MRB_ARGS_ARG(2,1)); /* 15.2.12.5.5  */
  mrb_define_method(mrb, a, "clear",           mrb_ary_clear_m,      MRB_ARGS_NONE());   /* 15.2.12.5.6  */
  mrb_define_method(mrb, a, "concat",          mrb_ary_concat_m,     MRB_ARGS_REQ(1));   /* 15.2.12.5.8  */
  mrb_define_method(mrb, a, "delete_at",       mrb_ary_delete_at,    MRB_ARGS_REQ(1));   /* 15.2.12.5.9  */
  mrb_define_method(mrb, a, "empty?",          mrb_ary_empty_p,      MRB_ARGS_NONE());   /* 15.2.12.5.12 */
  mrb_define_method(mrb, a, "first",           mrb_ary_first,        MRB_ARGS_OPT(1));   /* 15.2.12.5.13 */
  mrb_define_method(mrb, a, "index",           mrb_ary_index_m,      MRB_ARGS_REQ(1));   /* 15.2.12.5.14 */
  mrb_define_method(mrb, a, "initialize_copy", mrb_ary_replace_m,    MRB_ARGS_REQ(1));   /* 15.2.12.5.16 */
  mrb_define_method(mrb, a, "join",            mrb_ary_join_m,       MRB_ARGS_OPT(1));   /* 15.2.12.5.17 */
  mrb_define_method(mrb, a, "last",            mrb_ary_last,         MRB_ARGS_OPT(1));   /* 15.2.12.5.18 */
  mrb_define_method(mrb, a, "length",          mrb_ary_size,         MRB_ARGS_NONE());   /* 15.2.12.5.19 */
  mrb_define_method(mrb, a, "pop",             mrb_ary_pop,          MRB_ARGS_NONE());   /* 15.2.12.5.21 */
  mrb_define_method(mrb, a, "push",            mrb_ary_push_m,       MRB_ARGS_ANY());    /* 15.2.12.5.22 */
  mrb_define_method(mrb, a, "replace",         mrb_ary_replace_m,    MRB_ARGS_REQ(1));   /* 15.2.12.5.23 */
  mrb_define_method(mrb, a, "reverse",         mrb_ary_reverse,      MRB_ARGS_NONE());   /* 15.2.12.5.24 */
  mrb_define_method(mrb, a, "reverse!",        mrb_ary_reverse_bang, MRB_ARGS_NONE());   /* 15.2.12.5.25 */
  mrb_define_method(mrb, a, "rindex",          mrb_ary_rindex_m,     MRB_ARGS_REQ(1));   /* 15.2.12.5.26 */
  mrb_define_method(mrb, a, "shift",           mrb_ary_shift,        MRB_ARGS_NONE());   /* 15.2.12.5.27 */
  mrb_define_method(mrb, a, "size",            mrb_ary_size,         MRB_ARGS_NONE());   /* 15.2.12.5.28 */
  mrb_define_method(mrb, a, "slice",           mrb_ary_aget,         MRB_ARGS_ARG(1,1)); /* 15.2.12.5.29 */
  mrb_define_method(mrb, a, "unshift",         mrb_ary_unshift_m,    MRB_ARGS_ANY());    /* 15.2.12.5.30 */

  mrb_define_method(mrb, a, "__ary_eq",        mrb_ary_eq,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, a, "__ary_cmp",       mrb_ary_cmp,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, a, "__ary_index",     mrb_ary_index_m,      MRB_ARGS_REQ(1));   /* kept for mruby-array-ext */
  mrb_define_method(mrb, a, "__svalue",        mrb_ary_svalue,       MRB_ARGS_NONE());

  init_ary_each(mrb, a);
}