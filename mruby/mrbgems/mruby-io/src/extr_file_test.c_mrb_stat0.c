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
struct stat {int dummy; } ;
struct mrb_io {scalar_t__ fd; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_IO_ERROR ; 
 int LSTAT (char*,struct stat*) ; 
 int /*<<< orphan*/  RSTRING_CSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fstat (scalar_t__,struct stat*) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_data_get_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_io_type ; 
 int /*<<< orphan*/  mrb_locale_free (char*) ; 
 char* mrb_locale_from_utf8 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mrb_obj_is_kind_of (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int stat (char*,struct stat*) ; 

__attribute__((used)) static int
mrb_stat0(mrb_state *mrb, mrb_value obj, struct stat *st, int do_lstat)
{
  if (mrb_obj_is_kind_of(mrb, obj, mrb_class_get(mrb, "IO"))) {
    struct mrb_io *fptr;
    fptr = (struct mrb_io *)mrb_data_get_ptr(mrb, obj, &mrb_io_type);

    if (fptr && fptr->fd >= 0) {
      return fstat(fptr->fd, st);
    }

    mrb_raise(mrb, E_IO_ERROR, "closed stream");
    return -1;
  }
  else {
    char *path = mrb_locale_from_utf8(RSTRING_CSTR(mrb, obj), -1);
    int ret;
    if (do_lstat) {
      ret = LSTAT(path, st);
    } else {
      ret = stat(path, st);
    }
    mrb_locale_free(path);
    return ret;
  }
}