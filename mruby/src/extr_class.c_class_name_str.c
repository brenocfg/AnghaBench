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
struct RClass {scalar_t__ tt; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ MRB_TT_MODULE ; 
 int /*<<< orphan*/  mrb_class_path (int /*<<< orphan*/ *,struct RClass*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ptr_to_str (int /*<<< orphan*/ *,struct RClass*) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_cat_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
class_name_str(mrb_state *mrb, struct RClass* c)
{
  mrb_value path = mrb_class_path(mrb, c);
  if (mrb_nil_p(path)) {
    path = c->tt == MRB_TT_MODULE ? mrb_str_new_lit(mrb, "#<Module:") :
                                    mrb_str_new_lit(mrb, "#<Class:");
    mrb_str_cat_str(mrb, path, mrb_ptr_to_str(mrb, c));
    mrb_str_cat_lit(mrb, path, ">");
  }
  return path;
}