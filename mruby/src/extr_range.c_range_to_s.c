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
struct RRange {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  RANGE_BEG (struct RRange*) ; 
 int /*<<< orphan*/  RANGE_END (struct RRange*) ; 
 scalar_t__ RANGE_EXCL (struct RRange*) ; 
 int /*<<< orphan*/  mrb_obj_as_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RRange* mrb_range_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_cat_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
range_to_s(mrb_state *mrb, mrb_value range)
{
  mrb_value str, str2;
  struct RRange *r = mrb_range_ptr(mrb, range);

  str  = mrb_obj_as_string(mrb, RANGE_BEG(r));
  str2 = mrb_obj_as_string(mrb, RANGE_END(r));
  str  = mrb_str_dup(mrb, str);
  mrb_str_cat(mrb, str, "...", RANGE_EXCL(r) ? 3 : 2);
  mrb_str_cat_str(mrb, str, str2);

  return str;
}