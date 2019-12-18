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
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  fsize_t ;

/* Variables and functions */
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int send (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int sendto (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_send(mrb_state *mrb, mrb_value self)
{
  ssize_t n;
  mrb_int flags;
  mrb_value dest, mesg;

  dest = mrb_nil_value();
  mrb_get_args(mrb, "Si|S", &mesg, &flags, &dest);
  if (mrb_nil_p(dest)) {
    n = send(socket_fd(mrb, self), RSTRING_PTR(mesg), (fsize_t)RSTRING_LEN(mesg), (int)flags);
  } else {
    n = sendto(socket_fd(mrb, self), RSTRING_PTR(mesg), (fsize_t)RSTRING_LEN(mesg), (int)flags, (const struct sockaddr*)RSTRING_PTR(dest), (fsize_t)RSTRING_LEN(dest));
  }
  if (n == -1)
    mrb_sys_fail(mrb, "send");
  return mrb_fixnum_value((mrb_int)n);
}