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
struct stat {int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_io_fileno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_file_mtime(mrb_state *mrb, mrb_value self)
{
  mrb_value obj;
  struct stat st;
  int fd;

  obj = mrb_obj_value(mrb_class_get(mrb, "Time"));
  fd = (int)mrb_fixnum(mrb_io_fileno(mrb, self));
  if (fstat(fd, &st) == -1)
    return mrb_false_value();
  return mrb_funcall(mrb, obj, "at", 1, mrb_fixnum_value(st.st_mtime));
}