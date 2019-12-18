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
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_SEPARATOR ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_dup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * realpath (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_file_realpath(mrb_state *mrb, mrb_value klass)
{
  mrb_value pathname, dir_string, s, result;
  mrb_int argc;
  char *cpath;

  argc = mrb_get_args(mrb, "S|S", &pathname, &dir_string);
  if (argc == 2) {
    s = mrb_str_dup(mrb, dir_string);
    s = mrb_str_append(mrb, s, mrb_str_new_cstr(mrb, FILE_SEPARATOR));
    s = mrb_str_append(mrb, s, pathname);
    pathname = s;
  }
  cpath = mrb_locale_from_utf8(RSTRING_CSTR(mrb, pathname), -1);
  result = mrb_str_buf_new(mrb, PATH_MAX);
  if (realpath(cpath, RSTRING_PTR(result)) == NULL) {
    mrb_locale_free(cpath);
    mrb_sys_fail(mrb, cpath);
    return result;              /* not reached */
  }
  mrb_locale_free(cpath);
  mrb_str_resize(mrb, result, strlen(RSTRING_PTR(result)));
  return result;
}