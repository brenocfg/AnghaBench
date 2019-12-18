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
typedef  int ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/  mrb_str_buf_new (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_str_resize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int recvfrom (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_recvfrom(mrb_state *mrb, mrb_value self)
{
  ssize_t n;
  mrb_int maxlen, flags = 0;
  mrb_value ary, buf, sa;
  socklen_t socklen;

  mrb_get_args(mrb, "i|i", &maxlen, &flags);
  buf = mrb_str_buf_new(mrb, maxlen);
  socklen = sizeof(struct sockaddr_storage);
  sa = mrb_str_buf_new(mrb, socklen);
  n = recvfrom(socket_fd(mrb, self), RSTRING_PTR(buf), (fsize_t)maxlen, (int)flags, (struct sockaddr *)RSTRING_PTR(sa), &socklen);
  if (n == -1)
    mrb_sys_fail(mrb, "recvfrom");
  mrb_str_resize(mrb, buf, (mrb_int)n);
  mrb_str_resize(mrb, sa, (mrb_int)socklen);
  ary = mrb_ary_new_capa(mrb, 2);
  mrb_ary_push(mrb, ary, buf);
  mrb_ary_push(mrb, ary, sa);
  return ary;
}