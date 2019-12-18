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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_name_error (int /*<<< orphan*/ *,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 scalar_t__ mrb_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_symbol_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
struct_aref_sym(mrb_state *mrb, mrb_value obj, mrb_sym id)
{
  mrb_value members, *ptr;
  const mrb_value *ptr_members;
  mrb_int i, len;

  members = struct_members(mrb, obj);
  ptr_members = RARRAY_PTR(members);
  len = RARRAY_LEN(members);
  ptr = RSTRUCT_PTR(obj);
  for (i=0; i<len; i++) {
    mrb_value slot = ptr_members[i];
    if (mrb_symbol_p(slot) && mrb_symbol(slot) == id) {
      return ptr[i];
    }
  }
  mrb_name_error(mrb, id, "no member '%n' in struct", id);
  return mrb_nil_value();       /* not reached */
}