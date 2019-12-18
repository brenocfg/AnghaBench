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
typedef  int /*<<< orphan*/  rand_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_float_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rand_real (int /*<<< orphan*/ *) ; 
 int rand_uint32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value
random_rand(mrb_state *mrb, rand_state *t, mrb_value max)
{
  mrb_value value;

  if (mrb_fixnum(max) == 0) {
#ifndef MRB_WITHOUT_FLOAT
    value = mrb_float_value(mrb, rand_real(t));
#else
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Float not supported");
#endif
  }
  else {
    value = mrb_fixnum_value(rand_uint32(t) % mrb_fixnum(max));
  }

  return value;
}