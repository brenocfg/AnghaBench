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
struct RBasic {int dummy; } ;
struct RArray {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 scalar_t__ ARY_CAPA (struct RArray*) ; 
 scalar_t__ ARY_LEN (struct RArray*) ; 
 scalar_t__ ARY_PTR (struct RArray*) ; 
 int /*<<< orphan*/  ARY_SET_LEN (struct RArray*,scalar_t__) ; 
 int /*<<< orphan*/  array_copy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ary_expand_capa (int /*<<< orphan*/ *,struct RArray*,scalar_t__) ; 
 int /*<<< orphan*/  ary_modify (int /*<<< orphan*/ *,struct RArray*) ; 
 struct RArray* mrb_ary_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_write_barrier (int /*<<< orphan*/ *,struct RBasic*) ; 

__attribute__((used)) static mrb_value
mrb_ary_push_m(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv;
  mrb_int len, len2, alen;
  struct RArray *a;

  mrb_get_args(mrb, "*!", &argv, &alen);
  a = mrb_ary_ptr(self);
  ary_modify(mrb, a);
  len = ARY_LEN(a);
  len2 = len + alen;
  if (ARY_CAPA(a) < len2) {
    ary_expand_capa(mrb, a, len2);
  }
  array_copy(ARY_PTR(a)+len, argv, alen);
  ARY_SET_LEN(a, len2);
  mrb_write_barrier(mrb, (struct RBasic*)a);

  return self;
}