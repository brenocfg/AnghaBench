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

/* Variables and functions */
 scalar_t__ RARRAY_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ensure_hash_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_hash_new (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_f_hash(mrb_state *mrb, mrb_value self)
{
  mrb_value arg;

  mrb_get_args(mrb, "o", &arg);
  if (mrb_nil_p(arg) || (mrb_array_p(arg) && RARRAY_LEN(arg) == 0)) {
    return mrb_hash_new(mrb);
  }
  return mrb_ensure_hash_type(mrb, arg);
}