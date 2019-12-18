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
struct mrb_io {int fd2; int fd; int /*<<< orphan*/  writable; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  E_IO_ERROR ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 struct mrb_io* io_get_open_fptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

mrb_value
mrb_io_syswrite(mrb_state *mrb, mrb_value io)
{
  struct mrb_io *fptr;
  mrb_value str, buf;
  int fd, length;

  fptr = io_get_open_fptr(mrb, io);
  if (! fptr->writable) {
    mrb_raise(mrb, E_IO_ERROR, "not opened for writing");
  }

  mrb_get_args(mrb, "S", &str);
  buf = str;

  if (fptr->fd2 == -1) {
    fd = fptr->fd;
  } else {
    fd = fptr->fd2;
  }
  length = write(fd, RSTRING_PTR(buf), (fsize_t)RSTRING_LEN(buf));
  if (length == -1) {
    mrb_sys_fail(mrb, 0);
  }

  return mrb_fixnum_value(length);
}