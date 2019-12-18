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
 scalar_t__ CHMOD (char*,int) ; 
 int /*<<< orphan*/  RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ UNLINK (char*) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rename (char*,char*) ; 

__attribute__((used)) static mrb_value
mrb_file_s_rename(mrb_state *mrb, mrb_value obj)
{
  mrb_value from, to;
  char *src, *dst;

  mrb_get_args(mrb, "SS", &from, &to);
  src = mrb_locale_from_utf8(RSTRING_CSTR(mrb, from), -1);
  dst = mrb_locale_from_utf8(RSTRING_CSTR(mrb, to), -1);
  if (rename(src, dst) < 0) {
#if defined(_WIN32) || defined(_WIN64)
    if (CHMOD(dst, 0666) == 0 && UNLINK(dst) == 0 && rename(src, dst) == 0) {
      mrb_locale_free(src);
      mrb_locale_free(dst);
      return mrb_fixnum_value(0);
    }
#endif
    mrb_locale_free(src);
    mrb_locale_free(dst);
    mrb_sys_fail(mrb, RSTRING_CSTR(mrb, mrb_format(mrb, "(%v, %v)", from, to)));
    return mrb_fixnum_value(-1); /* not reached */
  }
  mrb_locale_free(src);
  mrb_locale_free(dst);
  return mrb_fixnum_value(0);
}