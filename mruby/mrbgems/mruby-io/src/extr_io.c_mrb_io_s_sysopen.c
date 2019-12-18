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
 char* RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mrb_cloexec_open (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int mrb_io_flags_to_modenum (int /*<<< orphan*/ *,int) ; 
 int mrb_io_modestr_to_flags (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 

mrb_value
mrb_io_s_sysopen(mrb_state *mrb, mrb_value klass)
{
  mrb_value path = mrb_nil_value();
  mrb_value mode = mrb_nil_value();
  mrb_int fd, perm = -1;
  const char *pat;
  int flags, modenum;

  mrb_get_args(mrb, "S|Si", &path, &mode, &perm);
  if (mrb_nil_p(mode)) {
    mode = mrb_str_new_cstr(mrb, "r");
  }
  if (perm < 0) {
    perm = 0666;
  }

  pat = RSTRING_CSTR(mrb, path);
  flags = mrb_io_modestr_to_flags(mrb, RSTRING_CSTR(mrb, mode));
  modenum = mrb_io_flags_to_modenum(mrb, flags);
  fd = mrb_cloexec_open(mrb, pat, modenum, perm);
  return mrb_fixnum_value(fd);
}