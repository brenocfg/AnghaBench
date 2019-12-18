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
typedef  int mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_bool_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 
 scalar_t__ str_eql (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_eql(mrb_state *mrb, mrb_value self)
{
  mrb_value str2;
  mrb_bool eql_p;

  mrb_get_args(mrb, "o", &str2);
  eql_p = (mrb_string_p(str2)) && str_eql(mrb, self, str2);

  return mrb_bool_value(eql_p);
}