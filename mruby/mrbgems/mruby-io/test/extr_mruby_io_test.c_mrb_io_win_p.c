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

/* Variables and functions */
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_true_value () ; 

mrb_value
mrb_io_win_p(mrb_state *mrb, mrb_value klass)
{
#if defined(_WIN32) || defined(_WIN64)
# if defined(__CYGWIN__) || defined(__CYGWIN32__)
  return mrb_false_value();
# else
  return mrb_true_value();
# endif
#else
  return mrb_false_value();
#endif
}