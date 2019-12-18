#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RProc {int dummy; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_method_t ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_METHOD_FROM_PROC (int /*<<< orphan*/ ,struct RProc*) ; 
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_define_method_raw (int /*<<< orphan*/ *,struct RClass*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_id_attrset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RProc* mrb_proc_new_cfunc_with_env (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_struct_ref ; 
 int /*<<< orphan*/  mrb_struct_set_m ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
make_struct_define_accessors(mrb_state *mrb, mrb_value members, struct RClass *c)
{
  const mrb_value *ptr_members = RARRAY_PTR(members);
  mrb_int i;
  mrb_int len = RARRAY_LEN(members);
  int ai = mrb_gc_arena_save(mrb);

  for (i=0; i<len; i++) {
    mrb_sym id = mrb_symbol(ptr_members[i]);
    mrb_method_t m;
    mrb_value at = mrb_fixnum_value(i);
    struct RProc *aref = mrb_proc_new_cfunc_with_env(mrb, mrb_struct_ref, 1, &at);
    struct RProc *aset = mrb_proc_new_cfunc_with_env(mrb, mrb_struct_set_m, 1, &at);
    MRB_METHOD_FROM_PROC(m, aref);
    mrb_define_method_raw(mrb, c, id, m);
    MRB_METHOD_FROM_PROC(m, aset);
    mrb_define_method_raw(mrb, c, mrb_id_attrset(mrb, id), m);
    mrb_gc_arena_restore(mrb, ai);
  }
}