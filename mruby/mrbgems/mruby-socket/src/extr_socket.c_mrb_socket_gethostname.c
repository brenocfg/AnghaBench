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
typedef  int /*<<< orphan*/  mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 int HOST_NAME_MAX ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ gethostname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_socket_gethostname(mrb_state *mrb, mrb_value cls)
{
  mrb_value buf;
  size_t bufsize;

#ifdef HOST_NAME_MAX
  bufsize = HOST_NAME_MAX + 1;
#else
  bufsize = 256;
#endif
  buf = mrb_str_buf_new(mrb, (mrb_int)bufsize);
  if (gethostname(RSTRING_PTR(buf), (fsize_t)bufsize) != 0)
    mrb_sys_fail(mrb, "gethostname");
  mrb_str_resize(mrb, buf, (mrb_int)strlen(RSTRING_PTR(buf)));
  return buf;
}