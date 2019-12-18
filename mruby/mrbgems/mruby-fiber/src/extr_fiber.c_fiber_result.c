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
typedef  int /*<<< orphan*/  const mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  const mrb_ary_new_from_values (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const mrb_nil_value () ; 

__attribute__((used)) static mrb_value
fiber_result(mrb_state *mrb, const mrb_value *a, mrb_int len)
{
  if (len == 0) return mrb_nil_value();
  if (len == 1) return a[0];
  return mrb_ary_new_from_values(mrb, len, a);
}