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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
mrb_socket_accept2(mrb_state *mrb, mrb_value klass)
{
  mrb_value ary, sastr;
  int s1;
  mrb_int s0;
  socklen_t socklen;

  mrb_get_args(mrb, "i", &s0);
  socklen = sizeof(struct sockaddr_storage);
  sastr = mrb_str_buf_new(mrb, socklen);
  s1 = (int)accept(s0, (struct sockaddr *)RSTRING_PTR(sastr), &socklen);
  if (s1 == -1) {
    mrb_sys_fail(mrb, "accept");
  }
  // XXX: possible descriptor leakage here!
  mrb_str_resize(mrb, sastr, socklen);
  ary = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, ary, mrb_fixnum_value(s1));
  mrb_ary_push(mrb, ary, sastr);
  return ary;
}