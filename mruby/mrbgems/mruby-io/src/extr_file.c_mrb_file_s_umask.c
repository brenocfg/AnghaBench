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

/* Variables and functions */
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

mrb_value
mrb_file_s_umask(mrb_state *mrb, mrb_value klass)
{
#if defined(_WIN32) || defined(_WIN64)
  /* nothing to do on windows */
  return mrb_fixnum_value(0);

#else
  mrb_int mask, omask;
  if (mrb_get_args(mrb, "|i", &mask) == 0) {
    omask = umask(0);
    umask(omask);
  } else {
    omask = umask(mask);
  }
  return mrb_fixnum_value(omask);
#endif
}