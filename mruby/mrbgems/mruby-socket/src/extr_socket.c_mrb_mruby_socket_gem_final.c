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
struct addrinfo {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  WSACleanup () ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  mrb_class_get (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_cptr (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_cptr_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_mod_cv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mrb_mruby_socket_gem_final(mrb_state* mrb)
{
  mrb_value ai;
  ai = mrb_mod_cv_get(mrb, mrb_class_get(mrb, "Addrinfo"), mrb_intern_lit(mrb, "_lastai"));
  if (mrb_cptr_p(ai)) {
    freeaddrinfo((struct addrinfo*)mrb_cptr(ai));
  }
#ifdef _WIN32
  WSACleanup();
#endif
}