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
typedef  int u_long ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int NO_ERROR ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_sys_fail (int /*<<< orphan*/ *,char*) ; 
 int socket_fd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_basicsocket_setnonblock(mrb_state *mrb, mrb_value self)
{
  int fd, flags;
  mrb_bool nonblocking;
#ifdef _WIN32
  u_long mode = 1;
#endif

  mrb_get_args(mrb, "b", &nonblocking);
  fd = socket_fd(mrb, self);
#ifdef _WIN32
  flags = ioctlsocket(fd, FIONBIO, &mode);
  if (flags != NO_ERROR)
    mrb_sys_fail(mrb, "ioctlsocket");
#else
  flags = fcntl(fd, F_GETFL, 0);
  if (flags == 1)
    mrb_sys_fail(mrb, "fcntl");
  if (nonblocking)
    flags |= O_NONBLOCK;
  else
    flags &= ~O_NONBLOCK;
  if (fcntl(fd, F_SETFL, flags) == -1)
    mrb_sys_fail(mrb, "fcntl");
#endif
  return mrb_nil_value();
}