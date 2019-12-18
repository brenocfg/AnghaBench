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
struct RClass {int /*<<< orphan*/  iv; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ detect_outer_loop (int /*<<< orphan*/ *,struct RClass*) ; 
 scalar_t__ find_class_sym (int /*<<< orphan*/ *,struct RClass*,struct RClass*) ; 
 int /*<<< orphan*/  iv_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iv_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mrb_class_name (int /*<<< orphan*/ *,struct RClass*) ; 
 int /*<<< orphan*/  mrb_field_write_barrier_value (int /*<<< orphan*/ *,struct RBasic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_capa (int /*<<< orphan*/ *,int) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 struct RClass* outer_class (int /*<<< orphan*/ *,struct RClass*) ; 

mrb_value
mrb_class_find_path(mrb_state *mrb, struct RClass *c)
{
  struct RClass *outer;
  mrb_value path;
  mrb_sym name;
  const char *str;
  mrb_int len;

  if (detect_outer_loop(mrb, c)) return mrb_nil_value();
  outer = outer_class(mrb, c);
  if (outer == NULL) return mrb_nil_value();
  name = find_class_sym(mrb, outer, c);
  if (name == 0) return mrb_nil_value();
  str = mrb_class_name(mrb, outer);
  path = mrb_str_new_capa(mrb, 40);
  mrb_str_cat_cstr(mrb, path, str);
  mrb_str_cat_cstr(mrb, path, "::");

  str = mrb_sym_name_len(mrb, name, &len);
  mrb_str_cat(mrb, path, str, len);
  if (RSTRING_PTR(path)[0] != '#') {
    iv_del(mrb, c->iv, mrb_intern_lit(mrb, "__outer__"), NULL);
    iv_put(mrb, c->iv, mrb_intern_lit(mrb, "__classname__"), path);
    mrb_field_write_barrier_value(mrb, (struct RBasic*)c, path);
    path = mrb_str_dup(mrb, path);
  }
  return path;
}