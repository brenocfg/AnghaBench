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
typedef  int /*<<< orphan*/  uc ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  i ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int IP_MULTICAST_LOOP ; 
 int IP_MULTICAST_TTL ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_false_p (int /*<<< orphan*/ ) ; 
 int mrb_fixnum (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_obj_classname (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_test (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_true_p (int /*<<< orphan*/ ) ; 
 int setsockopt (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_setsockopt(mrb_state *mrb, mrb_value self)
{
  int s;
  mrb_int argc, level = 0, optname;
  mrb_value optval, so;

  argc = mrb_get_args(mrb, "o|io", &so, &optname, &optval);
  if (argc == 3) {
    if (!mrb_fixnum_p(so)) {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "level is not an integer");
    }
    level = mrb_fixnum(so);
    if (mrb_string_p(optval)) {
      /* that's good */
    } else if (mrb_true_p(optval) || mrb_false_p(optval)) {
      mrb_int i = mrb_test(optval) ? 1 : 0;
      optval = mrb_str_new(mrb, (char*)&i, sizeof(i));
    } else if (mrb_fixnum_p(optval)) {
      if (optname == IP_MULTICAST_TTL || optname == IP_MULTICAST_LOOP) {
        char uc = (char)mrb_fixnum(optval);
        optval = mrb_str_new(mrb, &uc, sizeof(uc));
      } else {
        mrb_int i = mrb_fixnum(optval);
        optval = mrb_str_new(mrb, (char*)&i, sizeof(i));
      }
    } else {
      mrb_raise(mrb, E_ARGUMENT_ERROR, "optval should be true, false, an integer, or a string");
    }
  } else if (argc == 1) {
    if (strcmp(mrb_obj_classname(mrb, so), "Socket::Option") != 0)
      mrb_raise(mrb, E_ARGUMENT_ERROR, "not an instance of Socket::Option");
    level = mrb_fixnum(mrb_funcall(mrb, so, "level", 0));
    optname = mrb_fixnum(mrb_funcall(mrb, so, "optname", 0));
    optval = mrb_funcall(mrb, so, "data", 0);
  } else {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "wrong number of arguments (%i for 3)", argc);
  }

  s = socket_fd(mrb, self);
  if (setsockopt(s, (int)level, (int)optname, RSTRING_PTR(optval), (socklen_t)RSTRING_LEN(optval)) == -1)
    mrb_sys_fail(mrb, "setsockopt");
  return mrb_fixnum_value(0);
}