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
struct mrb_io {int /*<<< orphan*/  fd; int /*<<< orphan*/  readable; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  E_EOF_ERROR ; 
 int /*<<< orphan*/  E_IO_ERROR ; 
 int /*<<< orphan*/  RSTRING (int /*<<< orphan*/ ) ; 
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ io_get_open_fptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mrb_value
mrb_io_sysread(mrb_state *mrb, mrb_value io)
{
  struct mrb_io *fptr;
  mrb_value buf = mrb_nil_value();
  mrb_int maxlen;
  int ret;

  mrb_get_args(mrb, "i|S", &maxlen, &buf);
  if (maxlen < 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "negative expanding string size");
  }
  else if (maxlen == 0) {
    return mrb_str_new(mrb, NULL, maxlen);
  }

  if (mrb_nil_p(buf)) {
    buf = mrb_str_new(mrb, NULL, maxlen);
  }

  if (RSTRING_LEN(buf) != maxlen) {
    buf = mrb_str_resize(mrb, buf, maxlen);
  } else {
    mrb_str_modify(mrb, RSTRING(buf));
  }

  fptr = (struct mrb_io *)io_get_open_fptr(mrb, io);
  if (!fptr->readable) {
    mrb_raise(mrb, E_IO_ERROR, "not opened for reading");
  }
  ret = read(fptr->fd, RSTRING_PTR(buf), (fsize_t)maxlen);
  switch (ret) {
    case 0: /* EOF */
      if (maxlen == 0) {
        buf = mrb_str_new_cstr(mrb, "");
      } else {
        mrb_raise(mrb, E_EOF_ERROR, "sysread failed: End of File");
      }
      break;
    case -1: /* Error */
      mrb_sys_fail(mrb, "sysread failed");
      break;
    default:
      if (RSTRING_LEN(buf) != ret) {
        buf = mrb_str_resize(mrb, buf, ret);
      }
      break;
  }

  return buf;
}