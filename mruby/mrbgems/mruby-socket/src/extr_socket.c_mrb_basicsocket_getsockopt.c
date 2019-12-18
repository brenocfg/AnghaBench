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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int getsockopt (int,int,int,char*,int*) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ socket_family (int) ; 
 int socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_getsockopt(mrb_state *mrb, mrb_value self)
{
  char opt[8];
  int s;
  mrb_int family, level, optname;
  mrb_value c, data;
  socklen_t optlen;

  mrb_get_args(mrb, "ii", &level, &optname);
  s = socket_fd(mrb, self);
  optlen = sizeof(opt);
  if (getsockopt(s, (int)level, (int)optname, opt, &optlen) == -1)
    mrb_sys_fail(mrb, "getsockopt");
  c = mrb_const_get(mrb, mrb_obj_value(mrb_class_get(mrb, "Socket")), mrb_intern_lit(mrb, "Option"));
  family = socket_family(s);
  data = mrb_str_new(mrb, opt, optlen);
  return mrb_funcall(mrb, c, "new", 4, mrb_fixnum_value(family), mrb_fixnum_value(level), mrb_fixnum_value(optname), data);
}