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
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRUCT_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_new_capa (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_members (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_struct_to_h(mrb_state *mrb, mrb_value self)
{
  mrb_value members, ret;
  mrb_int i;

  members = struct_members(mrb, self);
  ret = mrb_hash_new_capa(mrb, RARRAY_LEN(members));

  for (i = 0; i < RARRAY_LEN(members); ++i) {
    mrb_hash_set(mrb, ret, RARRAY_PTR(members)[i], RSTRUCT_PTR(self)[i]);
  }

  return ret;
}